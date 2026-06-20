// DynLibUtils
// Copyright (C) 2023-2025 Vladimir Ezhikov (Wend4r) & Borys Komashchenko (Phoenix)
// Licensed under the MIT license. See LICENSE file in the project root for details.

#ifndef DYNLIBUTILS_MACROS_H
#define DYNLIBUTILS_MACROS_H

#pragma once

// Windows / Linux
#ifdef _WIN32
#	define DYNLIB_WIN_LINUX(win, linux) win
#elifdef __linux__
#	define DYNLIB_WIN_LINUX(win, linux) linux
#else
#	define DYNLIB_WIN_LINUX(...) static_assert(false, "Unsupported platform for DYNLIB_WIN_LINUX")
#endif

// Windows / Linux / macOS
#ifdef _WIN32
#	define DYNLIB_WIN_LINUX_MAC(win, linux, mac) win
#elifdef __linux__
#	define DYNLIB_WIN_LINUX_MAC(win, linux, mac) linux
#elifdef __APPLE__
#	define DYNLIB_WIN_LINUX_MAC(win, linux, mac) mac
#else
#	define DYNLIB_WIN_LINUX_MAC(...) static_assert(false, "Unsupported platform for DYNLIB_WIN_LINUX_MAC")
#endif

// Windows / Linux - 32-bit
#ifdef _WIN32
#	ifndef _WIN64
#		define DYNLIB_WIN32_LINUX32(win32, linux32) win32
#	endif
#elifdef __linux__
#	ifdef __i386__
#		define DYNLIB_WIN32_LINUX32(win32, linux32) linux32
#	endif
#endif
#ifndef DYNLIB_WIN32_LINUX32
#	define DYNLIB_WIN32_LINUX32(...) static_assert(false, "Unsupported platform for DYNLIB_WIN32_LINUX32")
#endif

// Windows / Linux - 64-bit
#ifdef _WIN64
#	define DYNLIB_WIN64_LINUX64(win64, linux64) win64
#elifdef __x86_64__
#	ifdef __linux__
#		define DYNLIB_WIN64_LINUX64(win64, linux64) linux64
#	endif
#endif
#ifndef DYNLIB_WIN64_LINUX64
#	define DYNLIB_WIN64_LINUX64(...) static_assert(false, "Unsupported platform for DYNLIB_WIN64_LINUX64")
#endif

// Win32 / Win64 / Linux32 / Linux64
#ifdef _WIN32
#	ifdef _WIN64
#		define DYNLIB_WIN_LINUX_X(win32, win64, linux32, linux64) win64
#	else
#		define DYNLIB_WIN_LINUX_X(win32, win64, linux32, linux64) win32
#	endif
#elifdef __linux__
#	ifdef __i386__
#		define DYNLIB_WIN_LINUX_X(win32, win64, linux32, linux64) linux32
#	elifdef __x86_64__
#		define DYNLIB_WIN_LINUX_X(win32, win64, linux32, linux64) linux64
#	endif
#endif
#ifndef DYNLIB_WIN_LINUX_X
#	define DYNLIB_WIN_LINUX_X(...) static_assert(false, "Unsupported platform for DYNLIB_WIN_LINUX_X")
#endif

// Windows / Linux / macOS - 64-bit
#ifdef _WIN32
#	ifdef _WIN64
#		define DYNLIB_WIN64_LINUX64_MAC64(win64, linux64, mac64) win64
#	endif
#elifdef __x86_64__
#	ifdef __linux__
#		define DYNLIB_WIN64_LINUX64_MAC64(win64, linux64, mac64) linux64
#	elifdef __APPLE__
#		define DYNLIB_WIN64_LINUX64_MAC64(win64, linux64, mac64) mac64
#	endif
#endif
#ifndef DYNLIB_WIN64_LINUX64_MAC64
#	define DYNLIB_WIN64_LINUX64_MAC64(...) static_assert(false, "Unsupported platform for DYNLIB_WIN64_LINUX64_MAC64")
#endif

// Generic platform selector: Win32/64, Linux32/64, macOS: x86/ARM
#ifdef _WIN32
#	ifdef _WIN64
#		define DYNLIB_PLATFORM_SELECT(win32, win64, linux32, linux64, mac_x86, mac_arm) win64
#	else
#		define DYNLIB_PLATFORM_SELECT(win32, win64, linux32, linux64, mac_x86, mac_arm) win32
#	endif
#elifdef __linux__
#	ifdef __x86_64__
#		define DYNLIB_PLATFORM_SELECT(win32, win64, linux32, linux64, mac_x86, mac_arm) linux64
#	elifdef __i386__
#		define DYNLIB_PLATFORM_SELECT(win32, win64, linux32, linux64, mac_x86, mac_arm) linux32
#	endif
#elifdef __APPLE__
#	ifdef __x86_64__
#		define DYNLIB_PLATFORM_SELECT(win32, win64, linux32, linux64, mac_x86, mac_arm) mac_x86
#	elifdef __aarch64__
#		define DYNLIB_PLATFORM_SELECT(win32, win64, linux32, linux64, mac_x86, mac_arm) mac_arm
#	endif
#endif
#ifndef DYNLIB_PLATFORM_SELECT
#	define DYNLIB_PLATFORM_SELECT(...) static_assert(false, "Unsupported platform for DYNLIB_PLATFORM_SELECT")
#endif

#endif // DYNLIBUTILS_MACROS_H
