#pragma once
#include "../../Vector/Vec2/Vec2.h"
#include "../../Vector/Vec3/Vec3.h"
#include "../../Vector/Vec4/Vec4.h"
namespace Math{
    struct MATH_API Mat4 {
            Vec4 C0;
            Vec4 C1;
            Vec4 C2;
            Vec4 C3;
    };
    MATH_API Mat4 Identity(float scala);
    MATH_API Mat4 Multiply(const Mat4& mat1, const Mat4& mat2);
    MATH_API Vec4 Multiply(const Vec4& vec, const Mat4& mat);
    MATH_API Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    MATH_API Mat4 Perspective(float fov, float aspect, float zNear, float zFar);
    MATH_API Mat4 Translate(const Mat4& mat,const Math::Vec3& translate);
    MATH_API Mat4 Scale(const Mat4& mat,const Math::Vec3& scale);
    //MATH_API Mat4 Rotate(const Mat4& mat,const Math::Vec3& rotation);
}
