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
// File Name: circle_component.cpp
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "circle_component.h"
#include "entity.h"

namespace omega
{
circle_component::circle_component(struct entity* owner) :
    component(owner) {
}

f32 circle_component::radius() const
{
    return m_parent->scale() * m_radius;
}
const vec2& circle_component::center() const
{
    return m_parent->position();
}

bool intersect(const circle_component& a, const circle_component& b)
{
    vec2 diff = a.center() - b.center();
    f32 distsq = diff.length_sq();
    f32 radiisq = a.radius() + b.radius();
    radiisq *= radiisq;

    return distsq <= radiisq;
}
} // namespace omega