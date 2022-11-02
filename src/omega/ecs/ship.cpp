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
// File Name: ship.cpp
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "ship.h"
#include "anim_sprite_component.h"
#include "omega/core/game.h"
#include <SDL.h>

namespace omega
{


ship::ship(game* game) : entity(game)
{
    auto* asc = new anim_sprite_component(this);

    utl::vector<SDL_Texture*> anims = {
        game->get_texture("./assets/sprites/ship01.png"),
        game->get_texture("./assets/sprites/ship02.png"),
        game->get_texture("./assets/sprites/ship03.png"),
        game->get_texture("./assets/sprites/ship04.png"),
    };
    asc->set_textures(anims);
}

void ship::update_entity(f32 delta)
{
    entity::update_entity(delta);
    vec2 pos = position();
    pos.x += m_right_speed * delta;
    pos.y += m_down_speed * delta;

    if (pos.x < 25.0f)
        pos.x = 25.0f;
    else if (pos.x > 500.0f)
        pos.x = 500.0f;
    if (pos.y < 25.0f)
        pos.y = 25.0f;
    else if (pos.y > 743.0f)
        pos.y = 743.0f;

    set_position(pos);
}
void ship::process_keyboard(const u8* state)
{
    m_right_speed = 0;
    m_down_speed  = 0;
    if (state [ SDL_SCANCODE_D ])
        m_right_speed += 250.0f;
    if (state [ SDL_SCANCODE_A ])
        m_right_speed -= 250.0f;
    if (state [ SDL_SCANCODE_S ])
        m_down_speed += 300.0f;
    if (state [ SDL_SCANCODE_W ])
        m_down_speed -= 300.0f;
}
} // namespace omega