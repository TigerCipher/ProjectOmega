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
// File Name: ship.cpp
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "ship.h"
#include "spritecomponent.h"
#include "anim_sprite_component.h"
#include "input_component.h"
#include "omega/core/game.h"
#include "laser.h"
#include <SDL.h>


namespace omega
{


ship::ship(game* game) : entity(game)
{
    //    auto* asc = new anim_sprite_component(this);
    //
    //    utl::vector<SDL_Texture*> anims = {
    //        game->get_texture("./assets/sprites/ship01.png"),
    //        game->get_texture("./assets/sprites/ship02.png"),
    //        game->get_texture("./assets/sprites/ship03.png"),
    //        game->get_texture("./assets/sprites/ship04.png"),
    //    };
    //    asc->set_textures(anims);

    auto* sc = new sprite_component(this, 150);
    sc->set_texture(game->get_texture("assets/sprites/new_ship.png"));

    auto* ic = new input_component(this);
    ic->set_key_forward(SDL_SCANCODE_W);
    ic->set_key_back(SDL_SCANCODE_S);
    ic->set_key_cw(SDL_SCANCODE_A);
    ic->set_key_ccw(SDL_SCANCODE_D);
    ic->set_max_forward_speed(300.0f);
    ic->set_max_angular_speed(math::two_pi);
}

void ship::update_entity(f32 delta)
{
    m_laser_cooldown -= delta;
}
void ship::input_entity(const u8* key_state)
{
    if (key_state [ SDL_SCANCODE_SPACE ] && m_laser_cooldown <= 0.0f)
    {
        OTRACE("Shooting laser");
        auto* lsr = new laser(get_game());
        lsr->set_position(position());
        lsr->set_rotation(rotation());
        m_laser_cooldown = 0.5f;
    }
}
} // namespace omega