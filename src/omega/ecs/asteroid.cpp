// ------------------------------------------------------------------------------
//
// ProjectOmega
//    Copyright 2023 Matthew Rogers
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
// File Name: asteroid.cpp
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "asteroid.h"
#include "omega/core/game.h"
#include "omega/util/util.h"
#include "spritecomponent.h"
#include "move_component.h"
#include "circle_component.h"

namespace omega
{
asteroid::asteroid(game* game) : entity(game)
{
    vec2 randpos = utl::random::vector(zero_vec2, vec2(1000, 800));
    set_position(randpos);

    set_rotation(utl::random::get_float(0.0f, math::two_pi));

    sprite_component* sc = new sprite_component(this);
    sc->set_texture(game->get_texture("assets/sprites/asteroid.png"));

    move_component* mc = new move_component(this);
    mc->set_forward_speed(150.0f);

    m_circle = new circle_component(this);
    m_circle->set_radius(40.0f);


    game->add_asteroid(this);
}

asteroid::~asteroid()
{
    // asteroid
    get_game()->remove_asteroid(this);
}
} // namespace omega