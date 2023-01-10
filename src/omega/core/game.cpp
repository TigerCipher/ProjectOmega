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

#include <SDL.h>
#include <SDL_image.h>

#include "omega/ecs/entity.h"
#include "omega/ecs/spritecomponent.h"
#include "omega/ecs/ship.h"
#include "omega/ecs/background_sprite_component.h"
#include "omega/ecs/asteroid.h"

#include <ranges>

namespace
{
s32 window_width  = 1000;
s32 window_height = 800;

} // namespace

namespace omega
{


bool game::initialize()
{
    s32 err = SDL_Init(SDL_INIT_VIDEO);
    if (err)
    {
        OERROR("Failed to initialize SDL: {}", SDL_GetError());
        return false;
    }
    m_window = SDL_CreateWindow("Project Omega", 200, 200, window_width, window_height, 0);

    if (!m_window)
    {
        OERROR("Failed to create window: {}", SDL_GetError());
        return false;
    }

    // Temporary
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        OERROR("Failed to create renderer: {}", SDL_GetError());
        return false;
    }

    err = IMG_Init(IMG_INIT_PNG);
    if (!err)
    {
        OERROR("Failed to initialize SDL Image");
        return false;
    }

    m_ticks = SDL_GetTicks();
    // Load game data
    m_ship = new ship(this);
    m_ship->set_position({100.0f, 384.0f});
    m_ship->set_scale(1.5f);

    auto* temp = new entity(this);
    temp->set_position({512, 384});
    auto* bg = new background_sprite_component(temp);
    bg->set_screen_size({(f32) window_width, (f32) window_height});
    utl::vector<SDL_Texture*> bgtex = {
        get_texture("./assets/sprites/bg01.png"),
        get_texture("./assets/sprites/bg02.png"),
    };
    bg->set_textures(bgtex);
    bg->set_scroll_speed(-100.0f);

    bg = new background_sprite_component(temp, 50);
    bg->set_screen_size({(f32) window_width, (f32) window_height});
    bgtex = {
        get_texture("./assets/sprites/stars.png"),
        get_texture("./assets/sprites/stars.png"),
    };
    bg->set_textures(bgtex);
    bg->set_scroll_speed(-200.0f);

    const u32 num_asts = 20;
    for (int i = 0; i < num_asts; ++i)
    {
        new asteroid(this);
    }

    return true;
}

void game::run()
{
    u32 st = SDL_GetTicks();
    while (m_running)
    {
        const u32 start_time = SDL_GetTicks();
        process_input();
        update();
        render();
        const u32   frame_time = SDL_GetTicks() - start_time;
        f32         fps        = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
        std::string title      = fmt::format(
            "Project Omega - FPS: {:.5f}",
            fps); // using fmt instead of std::format since not all compilers support std::format as of this writing
        SDL_SetWindowTitle(m_window, title.c_str());

        u32 elapsed = SDL_GetTicks() - st;
        if (elapsed >= 1000)
        {
            fmt::print("FPS: {:.5f}\n", fps);
            st = SDL_GetTicks();
        }
    }
}

void game::shutdown() const
{
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void game::add_entity(entity* ent)
{
    if (m_updating_entities)
        m_pending_entities.emplace_back(ent);
    else
        m_entities.emplace_back(ent);
}

void game::remove_entity(entity* ent)
{
    auto it = std::ranges::find(m_pending_entities, ent);
    if (it != m_pending_entities.end())
    {
        // Move entity to end of vector and pop off, this helps us avoid erase copies
        std::iter_swap(it, m_pending_entities.end() - 1);
        m_pending_entities.pop_back();
    }

    it = std::find(m_entities.begin(), m_entities.end(), ent);
    if (it != m_entities.end())
    {
        std::iter_swap(it, m_entities.end() - 1);
        m_entities.pop_back();
    }
}

void game::add_sprite(sprite_component* sprite)
{
    const s32 draw_order = sprite->draw_order();
    auto      it         = m_sprites.begin();
    while (it != m_sprites.end())
    {
        if (draw_order < (*it)->draw_order())
            break;
        ++it;
    }
    m_sprites.insert(it, sprite);
}

void game::remove_sprite(sprite_component* sprite)
{
    auto it = std::ranges::find(m_sprites, sprite);
    m_sprites.erase(it);
}

SDL_Texture* game::get_texture(const char* filename)
{
    if (m_textures.contains(filename))
        return m_textures [ filename ];
    SDL_Texture* tex        = load_texture(filename);
    m_textures [ filename ] = tex;
    return tex;
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
    if (key_state [ SDL_SCANCODE_ESCAPE ])
        m_running = false;

    m_ship->process_keyboard(key_state);
}

void game::update()
{
    // while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks + 16))
    //     ;

    f32 delta = (SDL_GetTicks() - (f32) m_ticks) / 1000.0f;
    m_ticks   = SDL_GetTicks();

    if (delta > 0.05f)
        delta = 0.0f;


    m_updating_entities = true;
    for (auto* ent : m_entities)
    {
        ent->update(delta);
    }
    m_updating_entities = false;

    for (auto* pent : m_pending_entities)
    {
        m_entities.emplace_back(pent);
    }
    m_pending_entities.clear();

    utl::vector<entity*> dead_entities;
    for (auto* ent : m_entities)
    {
        if (ent->get_state() == entity::DEAD)
        {
            dead_entities.emplace_back(ent);
        }
    }

    // Maybe we want to do more stuff with dead entities?

    // delete dead entities (auto removes them from vectors)
    for (auto* ent : dead_entities)
    {
        delete ent;
    }
}

void game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 52, 15, 15, 255);
    SDL_RenderClear(m_renderer);


    for (auto* spr : m_sprites)
    {
        spr->draw(m_renderer);
    }


    SDL_RenderPresent(m_renderer);
}

SDL_Texture* game::load_texture(const char* filename)
{
    SDL_Surface* surf = IMG_Load(filename);
    if (!surf)
    {
        OERROR("Failed to load texture file [{}]", filename);
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex)
    {
        OERROR("Failed to convert surface to texture [{}]", filename);
        return nullptr;
    }

    return tex;
}
void game::add_asteroid(asteroid* asteroid)
{
    m_asteroids.emplace_back(asteroid);
}
void game::remove_asteroid(asteroid* asteroid)
{
    auto iter = std::find(m_asteroids.begin(), m_asteroids.end(), asteroid);
    if (iter != m_asteroids.end())
    {
        m_asteroids.erase(iter);
    }
}
} // namespace omega
