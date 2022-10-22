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
#include "common.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace omega
{
game::game() : m_window(nullptr), m_running(true) {}

bool game::initialize()
{
    int err = SDL_Init(SDL_INIT_VIDEO);
    if (err)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    m_window = SDL_CreateWindow("Project Omega", 200, 200, 1000, 800, 0);

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
}

void game::update() {}

void game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 52, 15, 15, 255);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}
} // namespace omega
