//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <Core/Macros.hpp>

#if defined DYNAMIC_LINK
#define ENGINE_API DLL_EXPORT
#elif defined STATIC_LINK
#define ENGINE_API
#else
#define ENGINE_API DLL_IMPORT
#endif