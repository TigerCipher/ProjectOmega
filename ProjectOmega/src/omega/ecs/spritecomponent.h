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
// File Name: spritecomponent.h
// Date File Created: 10/23/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "component.h"

struct SDL_Renderer;
struct SDL_Texture;

namespace omega
{
class entity;

class sprite_component : public component
{
  public:
    sprite_component(entity* parent, s32 draw_order = 100);
    virtual ~sprite_component();

    virtual void draw(SDL_Renderer* renderer);
    virtual void set_texture(SDL_Texture* texture);

    s32 draw_order() const { return m_draw_order; }

    s32 width() const { return m_width; }

    s32 height() const { return m_height; }

  protected:
    s32          m_draw_order;
    SDL_Texture* m_texture = nullptr;
    s32          m_width   = 0;
    s32          m_height  = 0;
};
} // namespace omega