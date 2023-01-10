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
// File Name: move_component.h
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "component.h"

namespace omega
{

class move_component : public component
{
public:
    move_component(class entity* owner, s32 update_order = 10);

    void update(f32 delta) override;

    f32 angular_speed() const { return m_angular_speed; }
    f32 forward_speed() const { return m_forward_speed; }

    void set_angular_speed(f32 speed) { m_angular_speed = speed; }
    void set_forward_speed(f32 speed) { m_forward_speed = speed; }

private:
    f32 m_angular_speed = 0.0f;
    f32 m_forward_speed = 0.0f;
};

} // namespace omega
