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
// File Name: util.h
// Date File Created: 10/22/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include <random>
#include "maths.h"
#include "omega/core/types.h"

#define USE_STL_VECTOR 1

#if USE_STL_VECTOR
    #include <vector>
namespace omega::utl
{
template<typename T>
using vector = std::vector<T>;

}
#endif

namespace omega::utl
{
class random
{
public:
    static void init();

    static void seed(u32 seed);


    // float between min and max
    static f32 get_float(f32 min = 0.0f, f32 max = 1.0f);

    static s32 get_int(s32 min, s32 max);

    static vec2 vector(const vec2& min, const vec2& max);
    static vec3 vector(const vec3& min, const vec3& max);

private:
    static std::mt19937 generator;
};
} // namespace omega::utl
