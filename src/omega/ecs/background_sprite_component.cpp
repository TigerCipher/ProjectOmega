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
// File Name: background_sprite_component.cpp
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "background_sprite_component.h"
#include "entity.h"

#include <SDL.h>

namespace omega
{

void background_sprite_component::update(f32 delta)
{
    component::update(delta);
    for (auto& bg : m_bg_textures)
    {
        bg.offset.x += m_scroll_speed * delta;
        if (bg.offset.x < -m_screen_size.x)
            bg.offset.x = (m_bg_textures.size() - 1) * m_screen_size.x - 1;
    }
}
void background_sprite_component::draw(SDL_Renderer* renderer)
{
    for (auto& bg : m_bg_textures)
    {
        SDL_Rect r;
        r.w = (s32) m_screen_size.x;
        r.h = (s32) m_screen_size.y;
        r.x = (s32) (m_parent->position().x - r.w / 2 + bg.offset.x);
        r.y = (s32) (m_parent->position().y - r.h / 2 + bg.offset.y);

        SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
    }
}
void background_sprite_component::set_textures(const utl::vector<SDL_Texture*>& textures)
{
    s32 count = 0;
    for (auto tex : textures)
    {
        bg_texture temp;
        temp.texture  = tex;
        temp.offset.x = (f32)count * m_screen_size.x;
        temp.offset.y = 0;
        m_bg_textures.emplace_back(temp);
        ++count;
    }
}

} // namespace omega