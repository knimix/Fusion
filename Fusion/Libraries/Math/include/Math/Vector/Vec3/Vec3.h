#pragma once

#include "../../Core/Core.h"

namespace Math {
    struct MATH_API Vec3 {
        float x;
        float y;
        float z;
        bool operator ==(const Vec3& vec) const;
        bool operator !=(const Vec3& vec) const;
        Vec3 operator +(const Vec3& vec) const;
        Vec3 operator -(const Vec3& vec) const;
    };
    MATH_API Vec3 Add(const Vec3& vec1, const Vec3& vec2);
    MATH_API Vec3 Subtract(const Vec3& vec1, const Vec3& vec2);
    MATH_API Vec3 Multiply(const Vec3& vec1, const Vec3& vec2);
    MATH_API Vec3 Normalize(const Vec3& vec);
    MATH_API float Length(const Vec3& vec);
    MATH_API float Dot(const Vec3& vec1, const Vec3& vec2);
}
