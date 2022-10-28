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
// File Name: math.h
// Date File Created: 10/28/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "omega/core/types.h"
#include <cmath>
#include <limits>

namespace omega
{
constexpr f32 pi           = 3.1415926535f;
constexpr f32 two_pi       = pi * 2.0f;
constexpr f32 half_pi      = pi / 2.0f;
constexpr f32 infinity     = std::numeric_limits<f32>::infinity();
constexpr f32 neg_infinity = -infinity;

inline f32 to_radians(f32 degrees) { return degrees * pi / 180.0f; }

inline f32 to_degrees(f32 radians) { return radians * 180.0f / pi; }

template<typename T>
T max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template<typename T>
T min(const T& a, const T& b)
{
    return a < b ? a : b;
}

struct vec2
{
    f32 x = 0;
    f32 y = 0;
};

struct vec3
{
    f32 x = 0;
    f32 y = 0;
    f32 z = 0;
};

struct vec4
{
    f32 x = 0;
    f32 y = 0;
    f32 z = 0;
    f32 w = 0;
};

} // namespace omega
