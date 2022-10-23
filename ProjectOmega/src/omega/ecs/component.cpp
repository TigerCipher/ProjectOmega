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
// File Name: component.cpp
// Date File Created: 10/23/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "component.h"
#include "entity.h"


namespace omega
{
component::component(entity* parent, s32 update_order) : m_parent(parent), m_update_order(update_order)
{
    m_parent->add_component(this);
}

component::~component() { m_parent->remove_component(this); }

void component::update(f32 delta) {}
} // namespace omega
