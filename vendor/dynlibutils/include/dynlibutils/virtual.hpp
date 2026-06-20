// DynLibUtils
// Copyright (C) 2023-2025 Vladimir Ezhikov (Wend4r) & Borys Komashchenko (Phoenix)
// Licensed under the MIT license. See LICENSE file in the project root for details.

#ifndef DYNLIBUTILS_VIRTUAL_HPP
#define DYNLIBUTILS_VIRTUAL_HPP

#pragma once

#include "memaddr.hpp"

#include <bit>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#define DYNLIB_INVALID_VCALL -1

namespace DynLibUtils {

template<auto METHOD>
constexpr std::ptrdiff_t GetVirtualIndex() noexcept
{
	static_assert(std::is_member_function_pointer_v<decltype(METHOD)>, "Templated method must be a pointer-to-member-function");

	// --- Itanium C++ ABI: PMF.ptr = 1 + offset_in_bytes for virtual ones ---
	struct ItaniumPMF
	{
		union
		{
			std::ptrdiff_t addr;
			void* ptr;
		};

		std::ptrdiff_t adj;
	};
	constexpr union { decltype(METHOD) m; ItaniumPMF pmf; } u{ METHOD };

#if defined(_MSC_VER)
	auto *pAddr = reinterpret_cast<unsigned char *>(u.pmf.ptr);

	// If the thunk begins with 0xE9 (JMP rel32), skip over it to reach the real code:
	if (*pAddr == 0xE9)
	{
		// 0xE9 is a near jump with a 32‐bit relative displacement.
		// Compute the address after the jump target.
		pAddr += 5 /*size of the instruction*/ + *(unsigned long*)(pAddr + 1);
	}

	//AMs note:
	// Check whether it's a virtual function call
	// They look like this:
	// 004125A0 8B 01            mov        eax,dword ptr [ecx]
	// 004125A2 FF 60 04         jmp        dword ptr [eax+4]
	// 		==OR==
	// 00411B80 8B 01            mov        eax,dword ptr [ecx]
	// 00411B82 FF A0 18 03 00 00 jmp       dword ptr [eax+318h]

	// However, for vararg functions, they look like this:
	// 0048F0B0 8B 44 24 04      mov        eax,dword ptr [esp+4]
	// 0048F0B4 8B 00            mov        eax,dword ptr [eax]
	// 0048F0B6 FF 60 08         jmp        dword ptr [eax+8]
	// 		==OR==
	// 0048F0B0 8B 44 24 04      mov        eax,dword ptr [esp+4]
	// 0048F0B4 8B 00            mov        eax,dword ptr [eax]
	// 00411B82 FF A0 18 03 00 00 jmp       dword ptr [eax+318h]

	// With varargs, the this pointer is passed as if it was the first argument

	bool ok = false;

	// Now check for the common prologue patterns:
	//  (1)  mov eax, [ecx] / jmp [eax + imm8 or imm32]
	//  (2)  mov rax, [rcx] / jmp [rax + imm8 or imm32]   (for x64)
	if (pAddr[0] == 0x8B && pAddr[1] == 0x44 && pAddr[2] == 0x24 && pAddr[3] == 0x04 &&
	    pAddr[4] == 0x8B && pAddr[5] == 0x00)
	{
		// This matches:  mov eax, dword ptr [esp+4]; mov eax, [eax]
		pAddr += 6; ok = true;
	}
	else if (pAddr[0] == 0x8B && pAddr[1] == 0x01)
	{
		// This matches:  mov eax, [ecx]
		pAddr += 2; ok = true;
	}
	else if (pAddr[0] == 0x48 && pAddr[1] == 0x8B && pAddr[2] == 0x01)
	{
		// This matches:  mov rax, [rcx]    (64‐bit variant)
		pAddr += 3; ok = true;
	}

	if (!ok)
		return DYNLIB_INVALID_VCALL;

	// Next byte should be 0xFF, indicating an indirect jump through the vtable pointer:
	//   FF 60 imm8    => jmp [eax + imm8]    (8‐bit offset)
	//   FF A0 imm32   => jmp [eax + imm32]   (32‐bit offset)
	//   FF 20         => jmp [rsp] or other pattern for varargs (treated as index 0)
	if (*pAddr++ == 0xFF)
	{
		if (*pAddr == 0x60)
		{
			// 8‐bit displacement: next byte is imm8
			return static_cast<std::ptrdiff_t>(*++pAddr) / sizeof(void *);
		}
		else if (*pAddr == 0xA0)
		{
			// 32‐bit displacement: read a 32‐bit immediate
			return static_cast<std::ptrdiff_t>(*reinterpret_cast<unsigned int*>(++pAddr)) / sizeof(void *);
		}
		else if (*pAddr == 0x20)
		{
			// Pattern seen with varargs: treat as slot 0
			return 0;
		}
		else
		{
			return DYNLIB_INVALID_VCALL;
		}
	}

#elif defined(__GNUG__) || defined(__clang__)
	return (u.pmf.addr - 1u) / sizeof(void*);
#else
	static_assert(false, "Unsupported compiler");
#endif

	return DYNLIB_INVALID_VCALL;
}

// Provides an interface to manipulate and invoke entries from a class's virtual table (vtable).
class CVirtualTable
{
public: // Types.
	using CThis = CVirtualTable;

public: // Constructors.
	CVirtualTable() : m_pVTFs(nullptr) {}
	CVirtualTable(const CVirtualTable &) = default;
	CVirtualTable(CVirtualTable &&) = default;
	CVirtualTable(void* pClass) : m_pVTFs(*reinterpret_cast<void***>(pClass)) {} // Interprets the object’s first memory slot as a pointer to its vtable.
	CVirtualTable(CMemory pVTFs) : m_pVTFs(pVTFs.RCast<void**>()) {}

public: // Difference operators.
	// Compare two CVirtualTable instances by their integer representation of the vtable pointer 
	// for comparison in containers.
	bool operator==(const CVirtualTable& other) const { return m_diff == other.m_diff; }
	bool operator!=(const CVirtualTable& other) const { return !operator==(other); }
	bool operator< (const CVirtualTable& other) const { return m_diff < other.m_diff; }

public: // Getters.
	// Retrieve a reference to the vtable entry at index nIndex, cast to type R&.
	// R is expected to be a function pointer type or other pointer-like type.
	template<typename R> R& GetMethod(std::ptrdiff_t nIndex) { return reinterpret_cast<R &>(m_pVTFs[nIndex]); }
	template<typename R> R  GetMethod(std::ptrdiff_t nIndex) const { return reinterpret_cast<R>(m_pVTFs[nIndex]); }

public: // Callers.
	// Invoke a virtual function at index nIndex. 
	// R is the return type, Args... are the parameter types for the target function. 
	// The function pointer is assumed to have the signature R (*)(void*, Args...), 
	// where the first argument is the this-pointer.
	template<typename R, typename... Args> R CallMethod(std::ptrdiff_t nIndex, Args... args) { return GetMethod<R (*)(Args...)>(nIndex)(args...); }
	template<typename R, typename... Args> R CallMethod(std::ptrdiff_t nIndex, Args... args) const { return const_cast<CThis *>(this)->CallMethod(nIndex, args...); }

	// Union to store either:
	//  - m_pVTFs: pointer to an array of void* (the vtable).
	//  - m_diff: integer representation (pointer cast to ptrdiff_t) of the vtable address.
	// Using a union allows comparison and sorting by the vtable address.
	union
	{
		void** m_pVTFs;
		std::ptrdiff_t m_diff;
	};
}; // class CVirtualTable

class VirtualTable final : public CVirtualTable
{
public:
	using CBase = CVirtualTable;
	using CBase::CBase;
	// ...
}; // class VirtualTable

} // namespace DynLibUtils

#endif // DYNLIBUTILS_VIRTUAL_HPP
