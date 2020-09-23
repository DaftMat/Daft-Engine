//
// Created by mathis on 24/05/2020.
//
#pragma once
// clang-format off

/// --------------------------------------------------
/// Compiler identification
/// --------------------------------------------------
#if defined(__clang__)
#define CLANG_COMPILER
#elif defined(__GNUC__)
#define GCC_COMPILER
#elif defined(_MSC_VER)
#define MSVC_COMPILER
#else
#error Unsupported compiler.
#endif

#if defined(daft_Debug) || defined(daft_DEBUG) || defined(_DEBUG)
#define DEBUG
#endif
#if defined(daft_Release) || defined(daft_RELEASE) || defined(_RELEASE)
#define RELEASE
#endif
#if defined(daft_Trace) || defined(daft_TRACE) || defined(_TRACE)
#define TRACE
#endif

/// --------------------------------------------------
/// Platform identification
/// --------------------------------------------------
#if defined(_WIN32) || defined(_WIN64)          /// Windows
#define WIN_OS
#define __glext_h_  /// in case Qt tries to load OpenGL/glext.h
#include <Windows.h>
#   if defined(_M_X64)
#   define X64_ARCH
#   elif defined(_M_IX86)
#   define X86_ARCH
#   else
#   error Unsupported Operating System.
#   endif
#elif defined(__APPLE__) || defined(__MACH__) || defined(__MACOSX__)   /// Mac OS
#define MAC_OS
#define __gl3_h_    /// Qt (or other) may include OpenGL/gl3.h and
#define __glext_h_  /// OpenGL/glext.h which causes problems as glad already loads everything.
#   if defined(__i386__)
#   define X86_ARCH
#   elif defined(__x86_64__) || defined(__x86_64)
#   define X64_ARCH
#   else
#   error Unsupported architecture.
#   endif
#elif defined(__linux__) || defined(__CYGWIN__) /// Linux
#define LINUX_OS
#define __glext_h_ /// in case Qt tries to load gl/glext.h
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
#if defined(MSVC_COMPILER)
#   define DLL_EXPORT   __declspec(dllexport)
#   define DLL_IMPORT   __declspec(dllimport)
#elif defined(GCC_COMPILER) || defined(CLANG_COMPILER)
#   define DLL_EXPORT
#   define DLL_IMPORT
#else
#   error Unsupported platform.
#endif
// clang-format on