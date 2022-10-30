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
// File Name: spritecomponent.cpp
// Date File Created: 10/23/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "spritecomponent.h"

#include "entity.h"
#include "omega/core/game.h"

#include <SDL.h>

namespace omega
{
sprite_component::sprite_component(entity* parent, s32 draw_order) : component(parent), m_draw_order(draw_order)
{
    m_parent->get_game()->add_sprite(this);
}

sprite_component::~sprite_component()
{
    m_parent->get_game()->remove_sprite(this);
}

void sprite_component::draw(SDL_Renderer* renderer)
{
    if (!m_texture)
        return;
    SDL_Rect r;
    r.w = (int) (m_width * m_parent->scale());
    r.h = (int) (m_height * m_parent->scale());
    r.x = (int) (m_parent->position().x - r.w / 2);
    r.y = (int) (m_parent->position().y - r.h / 2);

    SDL_RenderCopyEx(renderer, m_texture, nullptr, &r, -to_degrees(m_parent->rotation()), nullptr, SDL_FLIP_NONE);
}

void sprite_component::set_texture(SDL_Texture* texture)
{
    m_texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &m_width, &m_height);
}
} // namespace omega
