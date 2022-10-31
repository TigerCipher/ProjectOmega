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
// File Name: ship.h
// Date File Created: 10/31/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include "entity.h"
namespace omega
{

class ship : public entity
{
public:
    ship(game* game);
    void update_entity(f32 delta) override;

    void process_keyboard(const u8* state);
    f32 right_speed() const { return m_right_speed; }
    f32 down_speed() const { return m_down_speed; }

private:
    f32 m_right_speed = 0;
    f32 m_down_speed = 0;

};

}


