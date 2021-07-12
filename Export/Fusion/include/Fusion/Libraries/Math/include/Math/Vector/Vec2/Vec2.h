#pragma once
#include "../../Core/Core.h"
namespace Math{
    struct MATH_API Vec2{
            float x;
            float y;
            bool operator == (const Vec2& vec) const;
            bool operator != (const Vec2& vec) const;
    };
    MATH_API Vec2 Add(const Vec2& vec1, const Vec2& vec2);
    MATH_API Vec2 Subtract(const Vec2& vec1, const Vec2& vec2);
    MATH_API Vec2 Multiply(const Vec2& vec1, const Vec2& vec2);
    MATH_API Vec2 Normalize(const Vec2& vec);
    MATH_API float Length(const Vec2& vec);
    MATH_API float Dot(const Vec2& vec1, const Vec2& vec2);
}
