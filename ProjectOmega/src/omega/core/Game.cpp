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

namespace omega
{
game::game() : m_window(nullptr), m_running(true) {}

bool game::initialize()
{
    int err = SDL_Init(SDL_INIT_VIDEO);
    if(err)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    m_window = SDL_CreateWindow("Project Omega", 200, 200, 1000, 800, 0);

    if(!m_window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void game::run()
{
    while(m_running)
    {
        process_input();
        update();
        render();
    }
}

void game::shutdown()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void game::process_input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        }
    }
}

void game::update() {}

void game::render() {}
} // namespace omega
