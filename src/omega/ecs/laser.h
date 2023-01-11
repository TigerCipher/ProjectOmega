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
// File Name: laser.h
// Date File Created: 1/10/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include "entity.h"

namespace omega
{

class laser : public entity
{
public:
    laser(class game* game);

    void update_entity(f32 delta) override;

private:
    class circle_component* m_circle;
    f32 m_death_timer = 0.5f;
};

} // namespace omega
