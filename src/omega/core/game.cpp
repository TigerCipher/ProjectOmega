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

namespace
{
s32 thickness     = 15;
s32 window_width  = 1000;
s32 window_height = 800;

} // namespace

namespace omega
{

class asteroid : public entity
{
  public:
    asteroid(game* game) : entity(game)
    {
        m_sprite = new sprite_component(this);
        m_sprite->set_texture(game->get_texture("./assets/sprites/asteroid.png"));
        set_position({100, 100});
    }
    virtual ~asteroid() { delete m_sprite; }
    void update_entity(f32 delta) override {}

  private:
    sprite_component* m_sprite;
};

game::game() : m_window(nullptr), m_running(true), m_ball_pos{1000.0f / 2.0f, 800.0f / 2.0f} {}

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

    // Load game data
    add_entity(new asteroid(this));
    return true;
}

void game::run()
{
    u32 st = SDL_GetTicks();
    while (m_running)
    {
        u32 start_time = SDL_GetTicks();
        process_input();
        update();
        render();
        u32         frame_time = SDL_GetTicks() - start_time;
        f32         fps        = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
        std::string title      = fmt::format("Project Omega - FPS: {:.5f}", fps); // using fmt instead of std::format since not all compilers support std::format as of this writing
        SDL_SetWindowTitle(m_window, title.c_str());

        u32 elapsed = SDL_GetTicks() - st;
        if (elapsed >= 1000)
        {
            fmt::print("FPS: {:.5f}\n", fps);
            st = SDL_GetTicks();
        }
    }
}

void game::shutdown()
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
    auto it = std::find(m_pending_entities.begin(), m_pending_entities.end(), ent);
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

    m_left_paddle_dir = 0;
    if (key_state [ SDL_SCANCODE_W ])
        --m_left_paddle_dir;
    if (key_state [ SDL_SCANCODE_S ])
        ++m_left_paddle_dir;

    m_right_paddle_dir = 0;
    if (key_state [ SDL_SCANCODE_UP ])
        --m_right_paddle_dir;
    if (key_state [ SDL_SCANCODE_DOWN ])
        ++m_right_paddle_dir;
    // if (key_state [ SDL_SCANCODE_D ]) __debugbreak();
}

void game::update()
{
    // while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks + 16))
    //     ;

    f32 delta = (SDL_GetTicks() - m_ticks) / 1000.0f;
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

    if (m_ball_pos.y <= thickness && m_ball_vel.y < 0)
        m_ball_vel.y = -m_ball_vel.y;
    if (m_ball_pos.y >= window_height - thickness && m_ball_vel.y > 0)
        m_ball_vel.y = -m_ball_vel.y;
    f32 diff = abs(m_ball_pos.y - m_left_paddle_pos.y);
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
} // namespace omega
