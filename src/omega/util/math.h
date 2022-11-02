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
// File Name: math.h
// Date File Created: 10/28/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "omega/core/types.h"
#include <cmath>
#include <limits>

namespace omega
{
namespace math
{
constexpr f32 pi           = 3.1415926535f;
constexpr f32 two_pi       = pi * 2.0f;
constexpr f32 half_pi      = pi / 2.0f;
constexpr f32 infinity     = std::numeric_limits<f32>::infinity();
constexpr f32 neg_infinity = -infinity;
constexpr f32 epsilon      = 0.001f;

inline f32 to_radians(f32 degrees)
{
    return degrees * pi / 180.0f;
}

inline f32 to_degrees(f32 radians)
{
    return radians * 180.0f / pi;
}

template<typename T>
T max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template<typename T>
T min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template<typename T>
T clamp(const T& val, const T& lower, const T& upper)
{
    return min(upper, max(lower, val));
}


inline bool near_zero(float val, float eps = epsilon)
{
    return fabs(val) <= eps;
}

inline f32 abs(f32 val)
{
    return fabs(val);
}

inline f32 cos(f32 angle)
{
    return cosf(angle);
}

inline f32 sin(f32 angle)
{
    return sinf(angle);
}

inline f32 tan(f32 angle)
{
    return tanf(angle);
}

inline f32 atan2(f32 y, f32 x)
{
    return atan2f(y, x);
}

inline f32 cot(f32 angle)
{
    return 1.0f / tan(angle);
}

inline f32 lerp(f32 a, f32 b, f32 f)
{
    return a + f * (b - a);
}

inline f32 sqrt(f32 val)
{
    return sqrtf(val);
}


} // namespace math

class vector2
{
public:
    // clang-format off
    union { f32 x, r, u; };
    union { f32 y, g, v; };
    // clang-format on

    vector2() = default;
    constexpr vector2(f32 _x, f32 _y) : x(_x), y(_y) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

    const f32* data() const { return &x; }

    friend vector2 operator+(const vector2& a, const vector2& b) { return {a.x + b.x, a.y + b.y}; }

    friend vector2 operator-(const vector2& a, const vector2& b) { return {a.x - b.x, a.y - b.y}; }

    friend vector2 operator*(const vector2& a, const vector2& b) { return {a.x * b.x, a.y * b.y}; }

    friend vector2 operator*(const vector2& v, f32 scalar) { return {v.x * scalar, v.y * scalar}; }

    friend vector2 operator*(f32 scalar, const vector2& v) { return {v.x * scalar, v.y * scalar}; }

    friend vector2 operator/(const vector2& a, const vector2& b) { return {a.x / b.x, a.y / b.y}; }

    friend vector2 operator/(const vector2& v, f32 scalar) { return {v.x / scalar, v.y / scalar}; }

    vector2& operator+=(const vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    vector2& operator-=(const vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    vector2& operator*=(const vector2& right)
    {
        x *= right.x;
        y *= right.y;
        return *this;
    }

    vector2& operator/=(const vector2& right)
    {
        x /= right.x;
        y /= right.y;
        return *this;
    }

    vector2& operator+=(f32 scalar)
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    vector2& operator-=(f32 scalar)
    {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    vector2& operator*=(f32 scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    vector2& operator/=(f32 scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    f32 length() const { return math::sqrt(length_sq()); }

    f32 length_sq() const { return x * x + y * y; }

    vector2& normalize()
    {
        const f32 len = length();
        x /= len;
        y /= len;
        return *this;
    }
};

class vector3
{
public:
    union
    {
        f32 x, r;
    };
    union
    {
        f32 y, g;
    };
    union
    {
        f32 z, b;
    };

    vector3() = default;
    constexpr vector3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

    const f32* data() const { return &x; }

    friend vector3 operator+(const vector3& a, const vector3& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }

    friend vector3 operator-(const vector3& a, const vector3& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }

    friend vector3 operator*(const vector3& a, const vector3& b) { return {a.x * b.x, a.y * b.y, a.z * b.z}; }

    friend vector3 operator/(const vector3& a, const vector3& b) { return {a.x / b.x, a.y / b.y, a.x / b.x}; }

    friend vector3 operator*(const vector3& v, f32 scalar) { return {v.x * scalar, v.y * scalar, v.z * scalar}; }

    friend vector3 operator*(f32 scalar, const vector3& v) { return {v.x * scalar, v.y * scalar, v.z * scalar}; }

    friend vector3 operator/(const vector3& v, f32 scalar) { return {v.x / scalar, v.y / scalar, v.z / scalar}; }

    vector3& operator+=(const vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    vector3& operator-=(const vector3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }

    vector3& operator*=(const vector3& right)
    {
        x *= right.x;
        y *= right.y;
        z *= right.z;
        return *this;
    }

    vector3& operator/=(const vector3& right)
    {
        x /= right.x;
        y /= right.y;
        z /= right.z;
        return *this;
    }

    vector3& operator+=(f32 scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    vector3& operator-=(f32 scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    vector3& operator*=(f32 scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    vector3& operator/=(f32 scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    f32 length() const { return math::sqrt(length_sq()); }

    f32 length_sq() const { return x * x + y * y + z * z; }

    vector3& normalize()
    {
        const f32 len = length();
        x /= len;
        y /= len;
        z /= len;
        return *this;
    }
};

namespace math
{
inline vector2 normalize(const vector2& v)
{
    vector2 temp = v;
    return temp.normalize();
}

inline f32 dot(const vector2& a, const vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

// Lerp from vector A to B by f
inline vector2 lerp(const vector2& a, const vector2& b, f32 f)
{
    return a + f * (b - a);
}

// reflect vector v about n (a normalized vector)
inline vector2 reflect(const vector2& v, const vector2& n)
{
    return v - 2.0f * dot(v, n) * n;
}

inline vector3 normalize(const vector3& v)
{
    vector3 temp = v;
    return temp.normalize();
}

inline f32 dot(const vector3& a, const vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vector3 cross(const vector3& a, const vector3& b)
{
    vector3 temp{};
    temp.x = a.y * b.z - a.z * b.y;
    temp.y = a.z * b.x - a.x * b.z;
    temp.z = a.x * b.y - a.y * b.x;
    return temp;
}

inline vector3 lerp(const vector3& a, const vector3& b, f32 f)
{
    return a + f * (b - a);
}

inline vector3 reflect(const vector3& v, const vector3& n)
{
    return v - 2.0f * dot(v, n) * n;
}

} // namespace math


constexpr vector2 zero_vec2{0, 0};
constexpr vector2 unitx_vec2{1, 0};
constexpr vector2 unity_vec2{0, 1};
constexpr vector2 neg_unitx_vec2{-1, 0};
constexpr vector2 neg_unity_vec2{0, -1};

using vec2 = vector2;

constexpr vector3 zero_vec3{0, 0, 0};
constexpr vector3 unitx_vec3{1, 0, 0};
constexpr vector3 unity_vec3{0, 1, 0};
constexpr vector3 unitz_vec3{0, 0, 1};
constexpr vector3 neg_unitx_vec3{-1, 0, 0};
constexpr vector3 neg_unity_vec3{0, -1, 0};
constexpr vector3 neg_unitz_vec3{0, 0, -1};

using vec3 = vector3;


struct vec4
{
    f32 x = 0;
    f32 y = 0;
    f32 z = 0;
    f32 w = 0;
};

} // namespace omega
