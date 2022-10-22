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
// File Name: game.cpp
// Date File Created: 10/21/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "game.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace
{
s32 thickness     = 15;
s32 window_width  = 1000;
s32 window_height = 800;
} // namespace

namespace omega
{
game::game() : m_window(nullptr), m_running(true), m_ball_pos(1000.0f / 2.0f, 800.0f / 2.0f) {}

bool game::initialize()
{
    int err = SDL_Init(SDL_INIT_VIDEO);
    if (err)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    m_window = SDL_CreateWindow("Project Omega", 200, 200, window_width, window_height, 0);

    if (!m_window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    // Temporary
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void game::run()
{
    while (m_running)
    {
        process_input();
        update();
        render();
    }
}

void game::shutdown()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void game::process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: m_running = false; break;
        }
    }

    const u8* key_state = SDL_GetKeyboardState(nullptr);
    if (key_state [ SDL_SCANCODE_ESCAPE ]) m_running = false;

    m_left_paddle_dir = 0;
    if (key_state [ SDL_SCANCODE_W ]) --m_left_paddle_dir;
    if (key_state [ SDL_SCANCODE_S ]) ++m_left_paddle_dir;

    m_right_paddle_dir = 0;
    if (key_state [ SDL_SCANCODE_UP ]) --m_right_paddle_dir;
    if (key_state [ SDL_SCANCODE_DOWN ]) ++m_right_paddle_dir;
    if (key_state [ SDL_SCANCODE_D ]) __debugbreak();
}

void game::update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks + 16))
        ;

    float delta = (SDL_GetTicks() - m_ticks) / 1000.0f;
    m_ticks     = SDL_GetTicks();

    if (delta > 0.05f) delta = 0.0f;

    if (m_left_paddle_dir)
    {
        m_left_paddle_pos.y += m_left_paddle_dir * 300.0f * delta;
        if (m_left_paddle_pos.y < 100 / 2.0f + thickness) // paddle height / 2 + paddle width
            m_left_paddle_pos.y = 100 / 2.0f + thickness;
        else if (m_left_paddle_pos.y > 800 - 100 / 2.0f - thickness)
            m_left_paddle_pos.y = 800 - 100 / 2.0f - 15;
    }

    if (m_right_paddle_dir)
    {
        m_right_paddle_pos.y += m_right_paddle_dir * 300.0f * delta;
        if (m_right_paddle_pos.y < 100 / 2.0f + thickness) // paddle height / 2 + paddle width
            m_right_paddle_pos.y = 100 / 2.0f + thickness;
        else if (m_right_paddle_pos.y > 800 - 100 / 2.0f - thickness)
            m_right_paddle_pos.y = 800 - 100 / 2.0f - 15;
    }

    m_ball_pos.x += m_ball_vel.x * delta;
    m_ball_pos.y += m_ball_vel.y * delta;

    if (m_ball_pos.y <= thickness && m_ball_vel.y < 0) m_ball_vel.y = -m_ball_vel.y;
    if (m_ball_pos.y >= window_height - thickness && m_ball_vel.y > 0) m_ball_vel.y = -m_ball_vel.y;
    float diff = abs(m_ball_pos.y - m_left_paddle_pos.y);
    if (diff <= 100 / 2.0f && m_ball_pos.x <= 25.0f && m_ball_pos.x >= 20.0f && m_ball_vel.x < 0)
        m_ball_vel.x = -m_ball_vel.x;
    diff = abs(m_ball_pos.y - m_right_paddle_pos.y);
    if (diff <= 100 / 2.0f && m_ball_pos.x >= (window_width - 25) && m_ball_pos.x <= (window_width - 20) &&
        m_ball_vel.x > 0)
        m_ball_vel.x = -m_ball_vel.x;
}

void game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 52, 15, 15, 255);
    SDL_RenderClear(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect top_wall{0, 0, window_width, thickness};
    SDL_Rect bottom_wall{0, window_height - thickness, window_width, thickness};
    SDL_RenderFillRect(m_renderer, &top_wall);
    SDL_RenderFillRect(m_renderer, &bottom_wall);

    SDL_Rect ball{(int) m_ball_pos.x - thickness / 2, (int) m_ball_pos.y - thickness / 2, thickness, thickness};
    SDL_Rect left_paddle{(int) m_left_paddle_pos.x - thickness / 2, (int) m_left_paddle_pos.y - 100 / 2, thickness,
                         100};
    SDL_Rect right_paddle{(int) m_right_paddle_pos.x - thickness / 2, (int) m_right_paddle_pos.y - 100 / 2, thickness,
                          100};
    SDL_RenderFillRect(m_renderer, &ball);
    SDL_RenderFillRect(m_renderer, &left_paddle);
    SDL_RenderFillRect(m_renderer, &right_paddle);

    SDL_RenderPresent(m_renderer);
}
} // namespace omega
