// DynLibUtils
// Copyright (C) 2023-2025 Vladimir Ezhikov (Wend4r) & Borys Komashchenko (Phoenix)
// Licensed under the MIT license. See LICENSE file in the project root for details.

#ifndef DYNLIBUTILS_MEMADDR_HPP
#define DYNLIBUTILS_MEMADDR_HPP

#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>

#ifdef __cpp_concepts
#	include <concepts>
#endif

#define DYNLIB_INVALID_MEMORY DynLibUtils::CMemory(nullptr)

namespace DynLibUtils {

#ifdef __cpp_concepts
// Concept for string output handler.
// Signature: void func(const std::string& sLine)
template<typename FUNC>
concept MemLineOutputFunc_t = requires(FUNC f, const std::string& sLine)
{
	{ f(sLine) } -> std::same_as<void>;
};

// Concept for byte-to-string conversion.
// Signature: std::pair<std::string, bool> func(std::size_t index, std::uint8_t byte)
// Returns (pair):  first  -> formatted byte string.
//                  second -> true to force line break after current byte.
template<typename FUNC>
concept MemByteToStringFunc_t = requires(FUNC f, std::size_t index, std::uint8_t byte)
{
	{ f(index, byte) } -> std::convertible_to<std::pair<std::string, bool>>;
};
#else
#define MemLineOutputFunc_t typename
#define MemByteToStringFunc_t typename
#endif

template<typename T = std::uint8_t, std::size_t SIZE = sizeof(T), std::size_t CHARS = std::max<std::size_t>(2, SIZE)>
inline char* MemToHexString_unsafe(char* pBuf, T val)
{
	std::uint8_t n = CHARS;

	while (n)
	{
		--n;
		pBuf[n] = "0123456789ABCDEF"[val & 0xFu];
		val >>= 4u;

	}

	return pBuf;
}

template<typename T = std::uint8_t, std::size_t SIZE = sizeof(T), std::size_t CHARS = std::max<std::size_t>(2, SIZE)>
inline std::string MemToHexString(T val)
{
	char sBuffer[CHARS];

	return std::string(MemToHexString_unsafe<T, SIZE, CHARS>(sBuffer, val), CHARS); // Small-string optimization?
}

inline bool IsHumanChar(std::uint8_t byte)
{
	return ' ' <= byte && byte <= '~';
}

inline char MemToHumanChar(std::uint8_t byte)
{
	return IsHumanChar(byte) ? static_cast<char>(byte) : '.';
}

template<std::size_t BYTES_PER_LINE>
inline constexpr auto g_funcDefaultMemToHex = [](std::size_t index, std::uint8_t byte) -> std::pair<std::string, bool>
{
	return std::make_pair(MemToHexString(byte), (index + 1) % BYTES_PER_LINE == 0);
};

template<std::size_t BYTES_PER_LINE = 8>
inline constexpr auto GetDefaultMemToHexFunc()
{
	return g_funcDefaultMemToHex<BYTES_PER_LINE>;
}

class CMemory
{
public:
	// Constructor ones.
	constexpr CMemory(const CMemory&) noexcept = default;
	constexpr CMemory(CMemory&&) noexcept = default;
	constexpr CMemory& operator=(const CMemory&) noexcept = default;
	constexpr CMemory& operator=(CMemory&& other) noexcept = default;
	constexpr CMemory(const std::uintptr_t addr) : m_addr(addr) {}
	constexpr CMemory(void* ptr = nullptr) : m_ptr(ptr) {}

	/// Conversion operators.
	constexpr operator void*() const noexcept { return GetPtr(); }
	constexpr operator std::uintptr_t() const noexcept { return GetAddr(); }

	/// Compare operators.
	bool operator==(const CMemory right) const noexcept { return m_addr == right.m_addr; }
	bool operator!=(const CMemory right) const noexcept { return !operator==(right); }
	bool operator<(const CMemory right) const noexcept { return m_addr < right.m_addr; }

	// Addition and subtraction operators.
	CMemory operator+(const std::size_t right) const noexcept { return Offset(right); }
	CMemory operator-(const std::size_t right) const noexcept { return Offset(-static_cast<std::ptrdiff_t>(right)); }
	CMemory operator+(const std::ptrdiff_t right) const noexcept { return Offset(right); }
	CMemory operator-(const std::ptrdiff_t right) const noexcept { return Offset(-right); }
	CMemory operator+(const CMemory right) const noexcept { return Offset(static_cast<std::ptrdiff_t>(right.m_addr)); }
	CMemory operator-(const CMemory right) const noexcept { return Offset(static_cast<std::ptrdiff_t>(right.m_addr)); }

	/// Cast methods.
	template<typename PTR> constexpr PTR CCast() const noexcept { return (PTR)m_addr; }
	template<typename PTR> constexpr PTR RCast() const noexcept { return reinterpret_cast<PTR>(m_addr); }
	template<typename PTR> constexpr PTR UCast() const noexcept { union { PTR cptr; std::uintptr_t addr; } cast; cast.addr = m_addr; return cast.cptr; }

	/// Access methods (getters).
	constexpr void* GetPtr() const noexcept { return m_ptr; }
	constexpr std::ptrdiff_t GetAddr() const noexcept { return m_addr; }
	template<typename T> constexpr T &GetRef() const noexcept { return *RCast<T*>(); }
	template<typename T> constexpr T Get() const { return GetRef<T>(); }

	/// Access methods (setters).
	constexpr void* SetPtr(void* pNew) noexcept { return m_ptr = pNew; }
	constexpr std::ptrdiff_t SetAddr(std::ptrdiff_t nNew) noexcept { return m_addr = nNew; }
	template<typename T> constexpr T &Set(const T &other) noexcept { return GetRef<T>() = other; }

	// Checks methods.
	bool IsValid() const noexcept { return GetPtr() != nullptr; }

	// Offset methods.
	CMemory Offset(const std::ptrdiff_t offset) const noexcept { return m_addr + offset; }
	CMemory& OffsetSelf(const std::ptrdiff_t offset) noexcept { m_addr += offset; return *this; }

	// Multi-level dereferencing methods.
	CMemory Deref(std::uintptr_t deref = 1, std::ptrdiff_t offset = 0) const noexcept
	{
		std::uintptr_t base = m_addr;

		while (base && deref--)
		{
			base = *reinterpret_cast<std::uintptr_t*>(base + offset);
		}

		return base;
	}
	CMemory& DerefSelf(int deref = 1, std::ptrdiff_t offset = 0) noexcept { while (m_addr && deref--) m_addr = *reinterpret_cast<std::uintptr_t*>(m_addr + offset); return *this; }

	CMemory FollowNearCall(const std::ptrdiff_t opcodeOffset = 0x1, const std::ptrdiff_t nextInstructionOffset = 0x5) const noexcept { return ResolveRelativeAddress(opcodeOffset, nextInstructionOffset); }
	CMemory& FollowNearCallSelf(const std::ptrdiff_t opcodeOffset = 0x1, const std::ptrdiff_t nextInstructionOffset = 0x5) noexcept { return ResolveRelativeAddressSelf(opcodeOffset, nextInstructionOffset); }

	CMemory ResolveRelativeAddress(const std::ptrdiff_t registerOffset = 0x0, const std::ptrdiff_t nextInstructionOffset = 0x4) const noexcept
	{
		const std::uintptr_t skipRegister = m_addr + registerOffset;
		const std::uintptr_t nextInstruction = m_addr + nextInstructionOffset;
		const std::int32_t relativeAddress = *reinterpret_cast<std::int32_t*>(skipRegister);

		return nextInstruction + relativeAddress;
	}
	CMemory& ResolveRelativeAddressSelf(const std::ptrdiff_t registerOffset = 0x0, const std::ptrdiff_t nextInstructionOffset = 0x4) noexcept
	{
		const std::uintptr_t skipRegister = m_addr + registerOffset;
		const std::uintptr_t nextInstruction = m_addr + nextInstructionOffset;
		const std::int32_t relativeAddress = *reinterpret_cast<std::int32_t*>(skipRegister);

		m_addr = nextInstruction + relativeAddress;

		return *this;
	}

	template<std::size_t BYTES_PER_LINE = 8, MemLineOutputFunc_t OUT_FUNC, MemByteToStringFunc_t TO_HEX_FUNC>
	std::size_t Dump(std::size_t size, OUT_FUNC funcOutput, TO_HEX_FUNC funcToHex = GetDefaultMemToHexFunc<BYTES_PER_LINE>()) const
	{
		constexpr std::size_t kCharsPerLine = BYTES_PER_LINE * 2;

		const auto* pData = RCast<const std::uint8_t*>();

		std::string sLine;
		sLine.reserve(128);

		std::string sFormated;
		sFormated.reserve(size);

		std::size_t nOutputCount = 0;

		for (std::size_t n = 0; n < size; ++n)
		{
			auto [sHex, bOutNextLine] = funcToHex(n, pData[n]);
			sLine += sHex;

			sFormated += MemToHumanChar(pData[n]);

			if ((n + 1) % BYTES_PER_LINE)
				sLine += ' ';

			if (bOutNextLine)
			{
				sLine += " |" + sFormated + "|\n";
				funcOutput(sLine);
				sLine.clear();
				sFormated.clear();

				nOutputCount++;
			}
		}

		// Handle final partial line.
		if (!sLine.empty())
		{
			std::size_t pad = kCharsPerLine - (size % kCharsPerLine);

			for (std::size_t i = 0; i < pad; ++i)
				sLine += "   ";

			sLine += (pad ? "|" : " |") + sFormated + "|\n";
			funcOutput(sLine);
			nOutputCount++;
		}

		return nOutputCount++;
	}

protected:
	union
	{
		void* m_ptr;
		std::uintptr_t m_addr;
	};
}; // class CMemory

template<typename T> 
class CMemoryView : public CMemory
{
public:
	using CBase = CMemory;
	using CBase::CBase;

	constexpr CMemoryView& operator=(const CMemory& copyFrom) noexcept { static_cast<CBase>(*this) = copyFrom; };

	using Element_t = T;
	using CThis = CMemoryView<T>;

	// Addition and subtraction operators (view ones).
	CMemory operator+(const std::size_t right) const noexcept { return Offset(right); }
	CMemory operator-(const std::size_t right) const noexcept { return Offset(-right); }
	CMemory operator+(const std::ptrdiff_t right) const noexcept { return Offset(right); }
	CMemory operator-(const std::ptrdiff_t right) const noexcept { return Offset(-right); }
	CMemory operator+(const CMemory right) const noexcept { return Offset(static_cast<std::ptrdiff_t>(right.GetAddr())); }
	CMemory operator-(const CMemory right) const noexcept { return Offset(static_cast<std::ptrdiff_t>(right.GetAddr())); }

	/// Cast methods (view ones).
	constexpr T* CCastView() const noexcept { return CBase::CCast<T*>(); }
	constexpr T* RCastView() const noexcept { return CBase::RCast<T*>(); }
	constexpr T* UCastView() const noexcept { return CBase::UCast<T*>(); }

	/// Access methods (view ones).
	constexpr T* GetPtr() const noexcept { return CBase::RCast<T*>(); }
	constexpr std::uintptr_t GetAddr() const noexcept { return CBase::RCast<T*>(); }
	constexpr T& GetRef() const noexcept { return *GetPtr(); }
	constexpr T Get() const { return GetRef(); }

	/// Offset methods (view ones; operators are used).
	CThis Offset(std::ptrdiff_t offset) const noexcept { return CThis(reinterpret_cast<T *>(CBase::m_addr) + offset); }
	CThis& OffsetSelf(std::ptrdiff_t offset) noexcept { reinterpret_cast<T *>(CBase::m_addr) += offset; return *this; }
}; // class CMemoryView

} // namespace DynLibUtils

#endif // DYNLIBUTILS_MEMADDR_HPP
