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
// File Name: entity.h
// Date File Created: 10/22/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "omega/common.h"


namespace omega
{
class game;
class component;

class entity
{
  public:
    enum state
    {
        ACTIVE,
        SUSPENDED,
        DEAD
    };

    explicit entity(game* game);

    virtual ~entity();

    void update(f32 delta);
    void update_components(f32 delta);

    virtual void update_entity(f32 delta);

    void add_component(component* comp);
    void remove_component(component* comp);

    state get_state() const { return m_state; }

    game* get_game() const { return m_game; }

    vec2 position() const { return m_position; }
    f32  scale() const { return m_scale; }
    f32  rotation() const { return m_rotation; }

    void set_position(const vec2& pos) { m_position = pos; }
    void set_scale(const f32 scale) { m_scale = scale; }
    void set_rotation(const f32 rot) { m_rotation = rot; }

    vec2 forward() const { return {math::cos(m_rotation), -math::sin(m_rotation)}; }

  private:
    state                   m_state;
    game*                   m_game;
    utl::vector<component*> m_components;

    // Transform data
    vec2 m_position;
    f32  m_scale;
    f32  m_rotation; // radians
};
} // namespace omega
