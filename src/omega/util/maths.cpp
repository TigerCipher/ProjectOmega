// ------------------------------------------------------------------------------
//
//
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
// File Name: maths.cpp
// Date File Created: 11/01/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "maths.h"


namespace omega::math
{
vector4 slerp(const vector4& a, const vector4& b, f32 f)
{
    const f32 raw_cosm = dot(a, b);
    f32       cosom;
    if (raw_cosm >= 0.0f)
        cosom = raw_cosm;
    else
        cosom = -raw_cosm;

    f32 scale0, scale1;
    if (cosom < 0.9999f)
    {
        const f32 omega   = acos(cosom);
        const f32 inv_sin = 1.0f / sin(omega);
        scale0            = sin((1.0f - f) * omega) * inv_sin;
        scale1            = sin(f * omega) * inv_sin;
    } else
    {
        scale0 = 1.0f - f;
        scale1 = f;
    }

    if (raw_cosm < 0.0f)
        scale1 = -scale1;

    vector4 ret{};
    ret.x = scale0 * a.x + scale1 * b.x;
    ret.y = scale0 * a.y + scale1 * b.y;
    ret.z = scale0 * a.z + scale1 * b.z;
    ret.w = scale0 * a.w + scale1 * b.w;
    return ret.normalize();
}

vector4 concatinate(const vector4& q, const vector4& p)
{
    vector4       ret{};
    const vector3 qv{q.x, q.y, q.z};
    const vector3 pv{p.x, p.y, p.z};
    const vector3 new_vec = p.w * qv + q.w * pv + cross(pv, qv);
    ret.x                 = new_vec.x;
    ret.y                 = new_vec.y;
    ret.z                 = new_vec.z;

    ret.w = p.w * q.w - dot(pv, qv);

    return ret;
}
} // namespace omega::math
