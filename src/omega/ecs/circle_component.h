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
// File Name: circle_component.h
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "component.h"

namespace omega
{

class circle_component : public component
{
public:
    circle_component(class entity* owner);

    void set_radius(f32 radius) { m_radius = radius; }
    f32 radius() const;

    const vec2& center() const;

private:
    f32 m_radius = 0.0f;
};

bool intersect(const circle_component& a, const circle_component& b);

} // namespace omega
