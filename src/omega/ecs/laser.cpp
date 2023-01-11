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
// File Name: laser.cpp
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "laser.h"
#include "omega/core/game.h"
#include "spritecomponent.h"
#include "move_component.h"
#include "circle_component.h"
#include "asteroid.h"

namespace omega
{
laser::laser(game* game) : entity(game)
{
    auto* sc = new sprite_component(this);
    sc->set_texture(game->get_texture("assets/sprites/laser.png"));

    auto* mc = new move_component(this);
    mc->set_forward_speed(800.0f);

    m_circle = new circle_component(this);
    m_circle->set_radius(11.0f);

}

void laser::update_entity(f32 delta)
{
    m_death_timer -= delta;
    if (m_death_timer <= 0.0f)
    {
        OTRACE("Killing laser");
        set_state(DEAD);
    } else
    {
        for (auto ast : get_game()->get_asteroids())
        {
            if (intersect(*m_circle, *(ast->get_circle())))
            {
                OTRACE("laser hit asteroid");
                set_state(DEAD);
                ast->set_state(DEAD);
                break;
            }
        }
    }
}
} // namespace omega