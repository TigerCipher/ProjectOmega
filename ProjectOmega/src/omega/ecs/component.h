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
// File Name: component.h
// Date File Created: 10/22/2022
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "omega/core/common.h"

namespace omega
{
class entity;

class component
{
public:
    explicit component(entity* parent, s32 update_order = 100);
    virtual ~component();

    virtual void update(f32 delta);
    s32 get_update_order() const { return m_update_order; }

protected:
    entity* m_parent;
    s32 m_update_order;
};
}
