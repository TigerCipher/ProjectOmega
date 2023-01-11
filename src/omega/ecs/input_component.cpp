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
// File Name: input_component.cpp
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "input_component.h"
#include "entity.h"

namespace omega
{

input_component::input_component(entity* entity) :
    move_component(entity) {}

void input_component::process_input(const u8* key_state)
{
    f32 forward_speed = 0.0f;

    if(key_state[m_key_forward])
        forward_speed += m_max_forward_speed;
    if(key_state[m_key_back])
        forward_speed -= m_max_forward_speed;

    set_forward_speed(forward_speed);

    f32 angular_speed = 0.0f;

    if(key_state[m_key_cw])
        angular_speed += m_max_angular_speed;
    if(key_state[m_key_ccw])
        angular_speed -= m_max_angular_speed;

    set_angular_speed(angular_speed);
}

} // namespace omega