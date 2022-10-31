// ------------------------------------------------------------------------------
//
// ProjectOmega
//    Copyright 2022 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: common.h
// Date File Created: 10/21/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "omega/core/types.h"
#include "omega/util/math.h"
#include "omega/util/util.h"
#include "omega/debug/logger.h"

#ifdef O_DEBUG
    #ifdef _WINDOWS
        #define DBG_BREAK() __debugbreak();
    #elif defined(O_UNIX)
        #include <signal.h>
        #define DBG_BREAK() raise(SIGTRAP)
    #else
        #define DBG_BREAK() assert(true)
    #endif
#else
    #define DBG_BREAK()
#endif

#ifdef O_DEBUG
    #include <cassert>
    #define OASSERT(condition, msg, ...)                                                                               \
        if (!(condition))                                                                                              \
        {                                                                                                              \
            OFATAL("An assertion occurred with the failed condition: ({}). " msg,                                      \
                   #condition __VA_OPT__(, ) __VA_ARGS__);                                                             \
            DBG_BREAK();                                                                                               \
        }
#else
    #define OASSERT(condition, msg, ...)
#endif
