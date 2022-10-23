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
// File Name: game.h
// Date File Created: 10/21/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once
#include "common.h"

struct SDL_Window;
struct SDL_Renderer;

namespace omega
{
class entity;

class game
{
  public:
    game();

    bool initialize();
    void run();
    void shutdown();

    void add_entity(entity* ent);
    void remove_entity(entity* ent);

  private:
    void process_input();
    void update();
    void render();

    SDL_Window* m_window;
    bool        m_running = false;

    utl::vector<entity*> m_entities;
    utl::vector<entity*> m_pending_entities;
    bool                 m_updating_entities = false;

    // Temporary
    SDL_Renderer* m_renderer;

    vec2 m_ball_pos;
    vec2 m_left_paddle_pos{0.0f, 800.0f / 2.0f};
    vec2 m_right_paddle_pos{1000.0f - 15.0f, 800.0f / 2.0f};
    u32  m_ticks            = 0;
    s32  m_left_paddle_dir  = 0;
    s32  m_right_paddle_dir = 0;
    vec2 m_ball_vel{-200.0f, 235.0f};
};
} // namespace omega
