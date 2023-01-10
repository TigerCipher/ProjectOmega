// ------------------------------------------------------------------------------
//
// ProjectOmega
//    Copyright 2023 Matthew Rogers
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
// File Name: util.cpp
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "util.h"

namespace omega::utl
{

std::mt19937 random::generator;

void random::init() {
    std::random_device rd;
    seed(rd());
}

void random::seed(u32 seed) {
    generator.seed(seed);
}


f32 random::get_float(f32 min, f32 max)
{
    std::uniform_real_distribution<f32> dist(min, max);
    return dist(generator);
}
s32 random::get_int(s32 min, s32 max)
{
    std::uniform_int_distribution<s32> dist(min, max);
    return dist(generator);
}
vec2 random::vector(const vec2& min, const vec2& max)
{
    vec2 r = vec2(get_float(), get_float());
    return min + (max - min) * r;
}
vec3 random::vector(const vec3& min, const vec3& max)
{
    vec3 r = vec3(get_float(), get_float(), get_float());
    return min + (max - min) * r;
}
} // namespace omega::utl