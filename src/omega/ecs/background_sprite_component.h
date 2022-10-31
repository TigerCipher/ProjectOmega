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
// File Name: background_sprite_component.h
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include "omega/common.h"
#include "spritecomponent.h"

namespace omega
{

class background_sprite_component : public sprite_component
{
public:
    background_sprite_component(class entity* parent, s32 draw_order = 10) : sprite_component(parent, draw_order) {}

    void update(f32 delta) override;
    void draw(SDL_Renderer* renderer) override;

    void set_textures(const utl::vector<SDL_Texture*>& textures);

    void set_screen_size(const vec2& size) { m_screen_size = size; }
    void set_scroll_speed(const f32 speed) { m_scroll_speed = speed; }
    f32 scroll_speed() const { return m_scroll_speed; }
private:
    struct bg_texture
    {
        SDL_Texture* texture = nullptr;
        vec2 offset{};
    };

    utl::vector<bg_texture> m_bg_textures;
    vec2 m_screen_size{};
    float m_scroll_speed = 0.0f;
};

} // namespace omega
