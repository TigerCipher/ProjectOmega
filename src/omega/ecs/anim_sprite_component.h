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
// File Name: anim_sprite_component.h
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "omega/common.h"
#include "spritecomponent.h"


namespace omega
{
class entity;
class anim_sprite_component : public sprite_component
{
public:
    anim_sprite_component(entity* parent, s32 draw_order = 100) : sprite_component(parent, draw_order) {}

    void update(f32 delta) override;

    void set_textures(const utl::vector<SDL_Texture*>& textures);

    float fps() const { return m_anim_fps; }

    void set_fps(const float fps) { m_anim_fps = fps; }

private:
    utl::vector<SDL_Texture*> m_anim_textures;
    float                     m_current_frame = 0.0f;
    float                     m_anim_fps      = 24.0f;
};

} // namespace omega
