#pragma once

#include "../../Core/Core.h"

namespace Math {
    struct MATH_API Vec4 {
        float x;
        float y;
        float z;
        float w;
        bool operator ==(const Vec4& vec) const;
        bool operator !=(const Vec4& vec) const;
        Vec4 operator +(const Vec4& vec) const;
        Vec4 operator -(const Vec4& vec) const;
    };
    MATH_API Vec4 Add(const Vec4& vec1, const Vec4& vec2);
    MATH_API Vec4 Subtract(const Vec4& vec1, const Vec4& vec2);
    MATH_API Vec4 Multiply(const Vec4& vec1, const Vec4& vec2);
    MATH_API Vec4 Normalize(const Vec4& vec);
    MATH_API float Length(const Vec4& vec);
    MATH_API float Dot(const Vec4& vec1, const Vec4& vec2);
}

