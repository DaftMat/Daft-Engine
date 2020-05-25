//
// Created by mathis on 24/05/2020.
//
#pragma once

/// --------------------------------------------------
/// Compiler identification
/// --------------------------------------------------
#if defined(__clang__)
#define CLANG_COMPILER
#elif defined(__GNUC__)
#define GCC_COMPILER
//#elif defined(_MSC_VER)
//#define MSVC_COMPILER
#else
#error Unsupported compiler.
#endif

/// --------------------------------------------------
/// Platform identification
/// --------------------------------------------------
/*#if defined(_WIN32) || defined(_WIN64)          /// Windows
#define WIN_OS
#   if defined(_M_X64)
#   define X64_ARCH
#   elif defined(_M_IX86)
#   define X86_ARCH
#   else
#   error Unsupported Operating System.
#   endif
#el*/#if defined(__APPLE__) || defined(__MACH__)   /// Mac OS
#define MAC_OS
#   if defined(__i386__)
#   define X86_ARCH
#   elif defined(__x86_64__) || defined(__x86_64)
#   define X64_ARCH
#   else
#   error Unsupported architecture.
#   endif
#elif defined(__linux__) || defined(__CYGWIN__) /// Linux
#define LINUX_OS
#   if defined(__i386)
#   define X86_ARCH
#   elif defined(__x86_64__) || defined(__x86_64)
#   define X64_ARCH
#   else
#   error Unsupported architecture.
#   endif
#else
#error Unsupported Operating System.
#endif

/// --------------------------------------------------
/// Library link identification + other
/// --------------------------------------------------
/*#if defined(MSVC_COMPILED)
#   define DLL_EXPORT   __declspec(dllexport)
#   define DLL_IMPORT   __declspec(dllimport)
#el*/#if defined(GCC_COMPILER) || defined(CLANG_COMPILER)
#   define DLL_EXPORT
#   define DLL_IMPORT
#else
#   error Unsupported platform.
#endif