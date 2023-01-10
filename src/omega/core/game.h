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
#include "omega/common.h"

#include <unordered_map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace omega
{
class entity;
class sprite_component;


class game
{
public:
    game() = default;

    bool initialize();
    void run();
    void shutdown() const;

    void add_entity(entity* ent);
    void remove_entity(entity* ent);

    void add_sprite(sprite_component* sprite);
    void remove_sprite(sprite_component* sprite);

    void add_asteroid(class asteroid* asteroid);
    void remove_asteroid(class asteroid* asteroid);

    utl::vector<class asteroid*>& get_asteroids() { return m_asteroids; }

    SDL_Texture* get_texture(const char* filename);

private:
    void process_input();
    void update();
    void render();

    SDL_Texture* load_texture(const char* filename);

    SDL_Window* m_window  = nullptr;
    bool        m_running = true;
    u32         m_ticks   = 0;

    utl::vector<entity*> m_entities;
    utl::vector<entity*> m_pending_entities;
    bool                 m_updating_entities = false;

    std::unordered_map<std::string, SDL_Texture*> m_textures;
    utl::vector<sprite_component*>                m_sprites;

    utl::vector<class asteroid*> m_asteroids;

    // Temporary
    SDL_Renderer* m_renderer = nullptr;

    class ship* m_ship;
};
} // namespace omega
