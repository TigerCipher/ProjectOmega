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
// File Name: anim_sprite_component.cpp
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "anim_sprite_component.h"

namespace omega
{
void anim_sprite_component::set_textures(const utl::vector<SDL_Texture*>& textures)
{
    m_anim_textures = textures;
    if (m_anim_textures.empty())
        return;
    m_current_frame = 0.0f;
    set_texture(m_anim_textures [ 0 ]);
}
void anim_sprite_component::update(f32 delta)
{
    component::update(delta);

    if(m_anim_textures.empty()) return;
    m_current_frame += m_anim_fps * delta;
    while(m_current_frame >= (f32)m_anim_textures.size())
    {
        m_current_frame -= (f32)m_anim_textures.size();
    }
    set_texture(m_anim_textures[(s32)m_current_frame]);
}
} // namespace omega