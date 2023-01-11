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
// File Name: input_component.h
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "move_component.h"

namespace omega
{

class input_component : public move_component
{
public:
    input_component(class entity* entity);

    void process_input(const u8* key_state) override;


    f32 max_forward_speed() const { return m_max_forward_speed; }
    f32 max_angular_speed() const { return m_max_angular_speed; }

    s32 key_back() const { return m_key_back; }
    s32 key_forward() const { return m_key_forward; }
    s32 key_cw() const { return m_key_cw; }
    s32 key_ccw() const { return m_key_ccw; }

    void set_max_forward_speed(f32 speed) { m_max_forward_speed = speed; }
    void set_max_angular_speed(f32 speed) { m_max_angular_speed = speed; }
    void set_key_forward(s32 key) { m_key_forward = key; }
    void set_key_back(s32 key) { m_key_back = key; }
    void set_key_cw(s32 key) { m_key_cw = key; }
    void set_key_ccw(s32 key) { m_key_ccw = key; }


private:
    f32 m_max_forward_speed = 1.0f;
    f32 m_max_angular_speed = 1.0f;

    s32 m_key_forward = 0;
    s32 m_key_back = 0;
    s32 m_key_cw = 0;
    s32 m_key_ccw = 0;
};

} // namespace omega
