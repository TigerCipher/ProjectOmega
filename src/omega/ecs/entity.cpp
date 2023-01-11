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
// File Name: entity.cpp
// Date File Created: 10/23/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "entity.h"

#include "component.h"
#include "omega/core/game.h"

#include <ranges>

namespace omega
{
entity::entity(game* game) : m_state(ACTIVE), m_game(game), m_position({0, 0}), m_scale(1.0f), m_rotation(0.0f)
{
    m_game->add_entity(this);
}

entity::~entity()
{
    m_game->remove_entity(this);
    while (!m_components.empty())
    {
        delete m_components.back();
    }
}

void entity::update(f32 delta)
{
    if (m_state != ACTIVE)
        return;
    update_components(delta);
    update_entity(delta);
}

void entity::update_components(f32 delta)
{
    for (auto* comp : m_components)
    {
        comp->update(delta);
    }
}

void entity::update_entity(f32 delta) {}

void entity::add_component(component* comp)
{
    const s32 order = comp->get_update_order();
    auto      it    = m_components.begin();
    while (it != m_components.end())
    {
        if (order < (*it)->get_update_order())
            break;
        ++it;
    }

    m_components.insert(it, comp);
}

void entity::remove_component(component* comp)
{
    if (const auto it = std::ranges::find(m_components, comp); it != m_components.end())
        m_components.erase(it);
}
void entity::process_input(const u8* key_state)
{
    if (m_state != ACTIVE)
        return;
    for (auto comp : m_components)
    {
        comp->process_input(key_state);
    }
    input_entity(key_state);
}
} // namespace omega
