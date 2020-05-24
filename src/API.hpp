//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <Core/Macros.hpp>

///TODO: replace ENGINE_API with the name you want, don't forget to use it in front of classes names.
#if defined DYNAMIC_LINK
#define ENGINE_API DLL_EXPORT
#elif defined STATIC_LINK
#define ENGINE_API
#else
#define ENGINE_API DLL_IMPORT
#endif