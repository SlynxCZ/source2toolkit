//
// DynLibUtils
// Copyright (C) 2023-2025 Vladimir Ezhikov (Wend4r) & Borys Komashchenko (Phoenix)
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#ifndef DYNLIBUTILS_VTHOOK_HPP
#define DYNLIBUTILS_VTHOOK_HPP
#pragma once

#include "memaddr.hpp"
#include "virtual.hpp"

#if _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	undef WIN32_LEAN_AND_MEAN
#else
#	include <sys/mman.h>
#	include <unistd.h>
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>

namespace DynLibUtils {

using ProtectFlags_t = unsigned long;

//=============================================================================
// VirtualUnprotector
//
// A RAII helper that temporarily changes the protection of a memory region 
// so that it becomes writable (and executable, if required). Upon destruction, 
// it restores the original protection flags.
//=============================================================================
class VirtualUnprotector final
{
public:
	//--------------------------------------------------------------------------
	// Constructor: Temporarily changes memory protection on [pTarget, pTarget+nLength)
	//
	// Parameters:
	//   - pTarget:  Starting address of the region to unprotect. This typically 
	//               points to code or data that needs to be overwritten at runtime. 
	//   - nLength:  Number of bytes to change. Default is sizeof(void*), which 
	//               is often enough to patch a single function pointer or small 
	//               instruction sequence.
	//
	// Behavior:
	//   - On Windows: 
	//       * Saves pTarget to m_pTarget and nLength to m_nLength. 
	//       * Calls VirtualProtect(pTarget, nLength, PAGE_EXECUTE_READWRITE, &m_nOldProtect) 
	//         to mark that region as Read/Write/Execute. 
	//       * m_nOldProtect receives the previous page protection flags. 
	//       * Asserts that VirtualProtect returned success (bIsUnprotected != 0).
	//
	//   - On POSIX (Linux/macOS): 
	//       * Queries page size via sysconf(_SC_PAGESIZE). 
	//       * Rounds pTarget down to the nearest page boundary (pPageStart). 
	//       * Rounds (pTarget + nLength) up to the next page boundary (pPageEnd). 
	//       * Computes nAligned = pPageEnd - pPageStart so that the entire range 
	//         of pages touched by the original region is included. 
	//       * Stores m_pTarget = pPageStart and m_nLength = nAligned. 
	//       * Sets m_nOldProtect = PROT_READ (assumes original region was at least readable). 
	//       * Calls mprotect(pPageStart, nAligned, PROT_READ | PROT_WRITE) to grant 
	//         write permission (while keeping read). 
	//       * Asserts that mprotect returned 0 (success).
	//
	// The constructor is noexcept: it does not throw exceptions. Failures to change 
	// page protection are caught by assert() in debug builds; in release builds, they 
	// proceed silently, which may mean writing to protected memory will fail.
	//--------------------------------------------------------------------------
	explicit VirtualUnprotector(void *pTarget, std::size_t nLength = sizeof(void*)) noexcept
	{
#if _WIN32
		m_nLength = nLength;
		m_pTarget = pTarget;

		[[maybe_unused]] bool bIsUnprotected = VirtualProtect(pTarget, nLength, PAGE_EXECUTE_READWRITE, &m_nOldProtect);
#else
		long pageSize = sysconf(_SC_PAGESIZE);

		assert(pageSize >= 0);

		auto nPageSize = static_cast<std::uintptr_t>(pageSize);

		// Compute page-aligned start address.
		auto pAddress = reinterpret_cast<std::uintptr_t>(pTarget);
		CMemory        pPageStart = pAddress & ~(nPageSize - 1l);
		std::uintptr_t pPageEnd = (pAddress + nLength + nPageSize - 1l) & ~(nPageSize - 1l); // Compute page-aligned end address (round up).
		auto nAligned = static_cast<std::size_t>(pPageEnd - pPageStart);

		// Assume the original protection was at least PROT_READ.
		m_nOldProtect = PROT_READ;
		m_nLength = nAligned;
		m_pTarget = pPageStart;

		bool bIsUnprotected = !mprotect(pPageStart, nAligned, PROT_READ | PROT_WRITE); // Grant write permission while keeping read permission.
#endif

		assert(bIsUnprotected);
	}

	//--------------------------------------------------------------------------
	// Destructor: Restores the original protection flags on the affected pages.
	//
	// Asserts that the restoration succeeds. If it fails in a debug build, the program 
	// will abort; in a release build, failure is silent (which may lead to incorrect 
	// memory protections afterward).
	//--------------------------------------------------------------------------
	~VirtualUnprotector()
	{
#if _WIN32
		DWORD origProtect;
		[[maybe_unused]] bool bIsUnprotected = VirtualProtect(m_pTarget, m_nLength, m_nOldProtect, &origProtect);
#else
		[[maybe_unused]] bool bIsUnprotected = !mprotect(m_pTarget, m_nLength, m_nOldProtect);
#endif

		assert(bIsUnprotected);
	}

private:
	ProtectFlags_t m_nOldProtect;
	std::size_t m_nLength;
	CMemory m_pTarget;
}; // class VirtualUnprotector

// A template class that allows hooking (i.e., replacing) a single virtual method 
// in a class’s vtable. It derives from CMemory to leverage memory‐reading/writing utilities.
// Template Parameters:
//   R    - The return type of the virtual function being hooked.
//   Args – Argument types of the virtual function being hooked. 
//          The first parameter must be a pointer to an (abstract) class type.
template<typename R, typename ...Args>
class CVTHook : public CMemory
{
public:
	using Function_t = R (*)(Args...); // Is the pointer‐to‐function type matching the signature of the virtual method.

	CVTHook() = default;
	CVTHook(const CVTHook &other) = delete;
	CVTHook(CVTHook &&other) : CMemory(std::exchange(static_cast<CMemory &>(other), DYNLIB_INVALID_MEMORY)), m_pOriginalFn(std::exchange(static_cast<CMemory &>(other.m_pOriginalFn), DYNLIB_INVALID_MEMORY)) {}
	~CVTHook()
	{
		if (IsHooked())
		{
			UnhookImpl();
		}
	}

	bool IsHooked() const noexcept { return IsValid(); } // Returns true if a hook is currently installed (i.e., we have a valid vtable slot pointer).
	void Clear() noexcept { SetPtr(nullptr); m_pOriginalFn = nullptr; }

	// Takes a CVirtualTable instance (which abstracts a vtable pointer) and a function pointer pFn. 
	// METHOD is a pointer‐to‐member function of the target class; GetVirtualIndex<METHOD>() 
	// computes the vtable index at compile time:
	//   - pVTable:  a CVirtualTable object pointing to the target class’s vtable.
	//   - nIndex (optional):  the zero‐based index into the vtable identifying which virtual slot to replace.
	//   - pFn:  the new function pointer to install in that slot.
	//
	//   Preconditions:
	//     * No hooked before (asserted)
	//     * Invalid vcall index (asserted)
	//   Postconditions:
	//     * Saves the address of the vtable entry.
	//     * Stores the original function pointer.
	//     * Overwrites the vtable entry.
	template<auto METHOD>
	void Hook(CVirtualTable pVTable, Function_t pFn) noexcept { Hook(pVTable, GetVirtualIndex<METHOD>(), pFn); } // This overload simply forwards to the index‐based Hook() below.
	void Hook(CVirtualTable pVTable, std::ptrdiff_t nIndex, Function_t pFn) noexcept
	{
		assert(!IsHooked());
		assert(nIndex != DYNLIB_INVALID_VCALL);

		SetPtr(&pVTable.GetMethod<void *>(nIndex));
		m_pOriginalFn = Deref();

		HookImpl(pFn);
	}

	// If no hook is installed, returns false.
	// Otherwise:
	//   * Restores the original function pointer. 
	//   * Resets internal state. 
	//   * Returns true.
	bool Unhook()
	{
		if (!IsHooked())
		{
			return false;
		}

		UnhookImpl();
		Clear();

		return true;
	}

	template<typename T = Function_t*> T GetTargetPtr() const noexcept { return RCast<T>(); } // Returns a pointer to the vtable slot that is currently hooked.
	template<typename T = Function_t> T GetOrigin() const noexcept { return m_pOriginalFn.RCast<T>(); } // Returns the original function pointer that was stored before hooking.

	// Must be invoked from within your hook replacement function if you wish to delegate 
	// to the original implementation’s logic. For example, in your hooked method body, 
	// you can call `hookInstance.Call(...);` to execute the original virtual method with  
	// the supplied arguments. If not called in the hook, the original logic will not run.
	R Call(Args... args) const { return GetOrigin<Function_t>()(args...); }

protected: // Implementation methods.
	void HookImpl(Function_t pfnTarget) noexcept
	{
		VirtualUnprotector unprotect(GetPtr());

		*GetTargetPtr() = pfnTarget;
	}

	void UnhookImpl() noexcept
	{
		VirtualUnprotector unprotect(GetPtr());

		*GetTargetPtr<void **>() = m_pOriginalFn.GetPtr();
	}

private:
	CMemory m_pOriginalFn;
}; // class CVTHook<R, Args...>

// A template class allows hooking a virtual function by providing a 
// lambda callback (which can capture state) instead of a raw function pointer.
// Template Parameters:
//   R    – Return type of the virtual function being hooked.
//   Args – Argument types of the virtual function being hooked. 
//          The first parameter must be a pointer to an (abstract) class type.
template<typename R, typename ...Args>
class CVTFHook : public CVTHook<R, Args...>
{
public:
	using CBase = CVTHook<R, Args...>;
	using CBase::CBase;
	using Function_t = std::function<R (Args...)>; // Allowing lambdas or other callable objects that match R(Args...) to be used as the hook target.

	void Clear() { CBase::Clear(); sm_callback = nullptr; }

	// Hooks takes labda callback:
	//   - pVTable:  CVirtualTable instance pointing to the target class’s vtable.
	//   - nIndex (optional):  Zero‐based index into the vtable to replace.
	//   - func:  Lambda callback to store and invoke when the hooked virtual function is called.
	template<auto METHOD> void Hook(CVirtualTable pVTable, Function_t &&func) noexcept { Hook(pVTable, GetVirtualIndex<METHOD>(), std::move(func)); }
	void Hook(CVirtualTable pVTable, std::ptrdiff_t nIndex, Function_t &&func) noexcept
	{
		assert(!sm_callback);

		sm_callback = std::move(func);
		CBase::Hook(pVTable, nIndex, +[](Args... args) -> R { return sm_callback(args...); });
	}

	bool Unhook()
	{
		bool bResult = CBase::Unhook();

		sm_callback = nullptr;

		return bResult;
	}

protected:
	inline static Function_t sm_callback;
}; // class CVTFHook<R, Args...>

// A template class represents generic manager for multiple virtual‐table hooks of the same signature.
// Template Parameter:
//   T — A hook element type, which must:
//         * Define a nested alias Function_t (e.g., R(*)(Args...)).
//         * Provide methods:
//             - void Hook(CVirtualTable, std::ptrdiff_t, Function_t)
//             - R    Call(C*, Args...) (or similar overloads)
//             - bool  Unhook(), etc.
//       Typical instantiations might be CVTHook<R,Args...> or CVTFHook<R,Args...>.
template<class T>
class CVTMHookBase
{
public:
	CVTMHookBase() = default;
	CVTMHookBase(const CVTMHookBase &other) = delete;
	CVTMHookBase(CVTMHookBase &&other) = default;

	using Element_t = T;
	using Function_t = typename Element_t::Function_t;

public:
	bool IsEmpty() const noexcept { return m_storage.empty(); } // Returns true if no hooks are currently stored.
	auto Find(const CVirtualTable pVTable) { return m_storage.equal_range(pVTable); } // Delimiting all entries (each Element_t) that were registered under that exact virtual table key.
	const auto End() const noexcept { return m_storage.cend(); } // Returns a const iterator pointing to the end (for comparison).
	void Clear() noexcept { m_storage.clear(); }

public:
	// Behavior:
	//   1. Creates a local entry instance (vth).
	//   2. Calls vth.Hook(pVTable, nIndex, vfunc) to perform the low‐level hook:
	//      * Saves the original function pointer in vth’s internal state.
	//      * Replaces the vtable entry [pVTable + nIndex] with vfunc.
	//   3. Inserts the newly‐constructed vth into m_storage under the key pVTable,
	//      returning an iterator to the inserted element.
	template<auto METHOD>
	auto AddHook(CVirtualTable pVTable, Function_t vfunc) { return AddHook(pVTable, GetVirtualIndex<METHOD>(), vfunc); }
	auto AddHook(CVirtualTable pVTable, std::ptrdiff_t nIndex, Function_t vfunc)
	{
		Element_t vth;

		vth.Hook(pVTable, nIndex, vfunc);

		return m_storage.emplace(pVTable, std::move(vth));
	}

	template<typename R, typename C, typename ...Args>
	R Call(C pThis, Args... args)
	{
		auto found = Find(CVirtualTable(pThis));

		if (found.first == found.second)
		{
			return {};
		}

		return found.first->second.Call(pThis, args...);
	}

	// Returns a vector containing the return values from each hook’s Call() invocation, 
	// in order of insertion. If no hooks were found for that vtable, returns an empty vector.
	template<typename R, typename C, typename ...Args>
	std::vector<R> CallAll(C pThis, Args... args)
	{
		std::vector<R> results;

		auto found = Find(CVirtualTable(pThis));

		if (found.first == found.second)
		{
			return results;
		}

		// results.reserve(vhooks.size());

		for (auto it = found.first; it != found.second; it++)
		{
			results.push_back(it->second.Call(pThis, args...));
		}

		return results;
	}

	// Returns true if at least one hook was executed; false if no hooks were found for that vtable.
	template<typename C, typename ...Args>
	bool CallAllNoReturn(C pThis, Args... args)
	{
		auto found = Find(CVirtualTable(pThis));

		if (found.first == found.second)
		{
			return false;
		}

		// results.reserve(vhooks.size());

		for (auto it = found.first; it != found.second; it++)
		{
			it->second.Call(pThis, args...);
		}

		return true;
	}
	// erases all hook elements associated with that vtable.
	//   - Returns the number of elements removed (std::size_t).
	std::size_t RemoveHook(CVirtualTable pVTable) { return m_storage.erase(pVTable); }

private:
	std::multimap<CVirtualTable, Element_t> m_storage;
}; // class CVTMHookBase<T, FUNC>

template<typename R, typename ...Args>
using CVTMHook = CVTMHookBase<CVTHook<R, Args...>>;

// A template class manages multiple virtual‐table hooks per class instance, where each hook can 
// execute multiple callbacks (std::function) when the original virtual method is invoked.
// Template Parameters:
//   R     – Return type of the hooked virtual method.
//   T     – Pointer of сlass type of the object whose virtual method is being hooked.
//   Args  – Argument types of the virtual method.
//
// Inheritance:
//   CVTFMHook inherits from CVTMHook<R, Args...>, which provides storage and basic hook‐installation 
//   logic for a multimap of CVirtualTable → hook elements. Each hook element in this context 
//   must itself know how to call a function pointer with signature R (Args...).
//
// CVTFMHook extends that by maintaining, for each hooked class (keyed by its CVirtualTable), a 
// vector of user‐supplied callbacks (Function_t = R(*)(T, Args...)). When the hooked virtual 
// function is called, all callbacks associated with that class’s vtable will be invoked.
//
// Note: This class assumes that the base hook element (Element_t) installed in the vtable will 
//       dispatch to a static trampoline that iterates over sm_vcallbacks[CVirtualTable(pClass)].
//
// Example usage:
//
//   struct MyClass {
//       virtual void OnEvent(int, float);
//   };
//
//   // Suppose we want to register multiple callbacks for MyClass::OnEvent.
//   CVTFMHook<void, MyClass*, int, float> hookManager;
//
//   // Add a callback lambda:
//   hookManager.AddHook<&MyClass::OnEvent>(
//       CVirtualTable(/*some instance of MyClass*/),
//       [](MyClass* self, int a, float b) {
//           // custom behavior here
//       }
//   );
//
//   // Later, when MyClass::OnEvent is called on an object, all registered callbacks for that object’s
//   // vtable will be executed in sequence.
//
//
// Implementation Details:
//   - sm_vcallbacks: A static std::map from CVirtualTable → std::vector<Function_t>.
//                     For each distinct vtable (i.e., each derived class or polymorphic type),
//                     we store a list of callbacks of type R(T, Args...).
//   - AddHook: Adds a new callback to sm_vcallbacks[vtable], and installs (via base AddHook) a
//              single vtable‐slot hook that dispatches to all callbacks in the vector.
//   - RemoveHook: Erases the entry for a given CVirtualTable from sm_vcallbacks, then removes
//                 all registered hooks in the base class for that vtable.
//   - Clear:     Clears sm_vcallbacks entirely and then clears all hooks from the base class.
//
// Disclaimer: This code snippet assumes that Element_t (from the base class) is capable of
//             installing a hook that, when invoked, calls a single raw function pointer that
//             matches R(T, Args...). The static lambda in AddHook is that trampoline.
//
//=============================================================================
template<typename R, class T, typename ...Args>
class CVTFMHook : public CVTMHook<R, T, Args...>
{
public:
	using Base_t = CVTMHook<R, T, Args...>;
	using Function_t = std::function<R (T, Args...)>;
	using Functions_t = std::vector<std::function<R (T, Args...)>>;

	// AddHook (by index):
	//   Installs or appends a callback for a given vtable index.
	//
	//   Parameters:
	//     - pVTable:  A CVirtualTable instance representing the target class’s vtable.
	//     - nIndex (optional):  Zero‐based index into the vtable indicating which virtual slot to hook.
	//     - funcCallback:  The std::function<R(T, Args...)> to append to the callback list.
	//
	//   Behavior:
	//     1. Insert or append funcCallback into the static map sm_vcallbacks at key `pVTable`.
	//     2. Call the base class’s
	//      - The unary '+' ensures the lambda is converted to a raw function pointer of type Function_t.
	//      - When the hooked method is invoked on an object `pClass`, the trampoline lambda:
	//          a) Constructs a CVirtualTable(pClass) to look up the correct list of callbacks.
	//          b) Retrieves `callbacks`, which is a std::vector<Function_t> stored in sm_vcallbacks.
	//          c) Iterates through each callback in the vector and invokes it with (pClass, args...).
	template<auto METHOD>
	void AddHook(CVirtualTable pVTable, Function_t funcCallback) { return AddHook(pVTable, GetVirtualIndex<METHOD>(), funcCallback); }
	void AddHook(CVirtualTable pVTable, std::ptrdiff_t nIndex, Function_t funcCallback)
	{
		auto found = sm_vcallbacks.find(pVTable);

		if(found != sm_vcallbacks.cend())
		{
			found->second.push_back(std::move(funcCallback));
		}
		else
		{
			sm_vcallbacks.emplace(pVTable, Functions_t{std::move(funcCallback)});
		}

		Base_t::AddHook(pVTable, nIndex,
			+[](T pClass, Args... args) -> R
			{
				auto found = sm_vcallbacks.find(CVirtualTable(pClass));

				assert(found != sm_vcallbacks.cend());

				auto &callbacks = found->second;

				R result {};

				for (auto it : callbacks)
				{
					result = it(pClass, args...);
				}

				return result;
			}
		);
	}

	bool RemoveHook(CVirtualTable pVTable)
	{
		sm_vcallbacks.erase(pVTable);

		return Base_t::RemoveHook(pVTable) != 0;
	}

	void Clear()
	{
		sm_vcallbacks.clear();
		Base_t::Clear();
	}

protected:
	inline static std::map<CVirtualTable, Functions_t> sm_vcallbacks;
}; // class CVTFHookSet<R, T, Args...>

// ========================================================================================
// CVTHookAutoBase: Automatic wrapper for member function pointers
// ========================================================================================
//
// This template uses partial specialization to inherit from a user-defined template T
// instantiated with the signature of a given member function pointer. The T template must
// accept the return type, a pointer to the class, and all method argument types.
//
// This pattern enables generic generation of function hooks or proxies with minimal
// boilerplate: types are deduced from the function pointer automatically.
//
template<template<typename, typename...> class T, auto METHOD>
class CVTHookAutoBase;

// Partial specialization for member function pointers:
// Inherits from T<R, C*, Args...> for the signature R (C::*)(Args...).
template<template<typename, typename...> class T, typename R, typename C, typename ...Args, R (C::*METHOD)(Args...)>
class CVTHookAutoBase<T, METHOD> : public T<R, C*, Args...>
{
public:
	using CBase = T<R, C*, Args...>;
	using CBase::CBase;

	// Wend4r (Linux): don't allow typeinfo/rtti to be generated for templated C argument.
	DYNLIB_FORCE_INLINE void Hook(CVirtualTable pVTable, typename CBase::Function_t &&func) noexcept
	{
		CBase::Hook(pVTable, GetVirtualIndex<METHOD>(), std::move(func));
	}
}; // CVTHookAutoBase<T, R, C, Args...>

// ========================================================================================
// Alias templates for concise hook type declarations
// ========================================================================================
//
// These aliases allow you to declare an automatic hook/wrapper type for any member
// function by simply specifying its pointer:
//
//   CVTHookAuto<&MyClass::SomeVirtualMethod> myHook;
//
template<auto METHOD> using CVTHookAuto = CVTHookAutoBase<CVTHook, METHOD>;
template<auto METHOD> using CVTFHookAuto = CVTHookAutoBase<CVTFHook, METHOD>;

// A final alias of CVTHook class.
template<typename R, typename ...Args>
class VTHook final : public CVTHook<R, Args...>
{
public:
	using CBase = CVTHook<R, Args...>;
	using CBase::CBase;
}; // class VTHook<R, Args...>

// A final alias of CVTFHook class.
template<typename R, typename ...Args>
class VTFHook final : public CVTFHook<R, Args...>
{
public:
	using CBase = CVTFHook<R, Args...>;
	using CBase::CBase;
}; // class VTFHook<R, Args...>

// A final alias of CVTMHook class.
template<typename R, typename ...Args>
class VTMHook final : public CVTMHook<R, Args...>
{
public:
	using CBase = CVTMHook<R, Args...>;
	using CBase::CBase;
}; // class VTMHook<R, Args...>

// A final alias of CVTFMHook class.
template<typename R, typename ...Args>
class VTFMHook final : public CVTFMHook<R, Args...>
{
public:
	using CBase = CVTFMHook<R, Args...>;
	using CBase::CBase;
}; // class VTFMHook<R, Args...>

} // namespace DynLibUtils

#endif // DYNLIBUTILS_VTHOOK_HPP
