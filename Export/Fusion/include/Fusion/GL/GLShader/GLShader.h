#pragma once

#include <Math/Matrix/Mat4/Mat4.h>

namespace Fusion::GL {
    void CreateShader(const char* vertex, const char* fragment, unsigned int& shader);
    void BindShader(unsigned int& shader);
    void UnbindShader(unsigned int& shader);
    void SetUniformInt(unsigned int& shader, const char* name, int value);
    void SetUniformIntArray(unsigned int& shader, const char* name, int size, const int* data);
    void SetUniformFloat(unsigned int& shader, const char* name, float value);
    void SetUniformFloatArray(unsigned int& shader, const char* name, int size, const float* data);
    void SetUniformVec2(unsigned int& shader, const char* name, const Math::Vec2& vec2);
    void SetUniformVec2Array(unsigned int& shader, const char* name, int size, const float* data);
    void SetUniformVec3(unsigned int& shader, const char* name, const Math::Vec3& vec3);
    void SetUniformVec3Array(unsigned int& shader, const char* name, int size, const float* data);
    void SetUniformVec4(unsigned int& shader, const char* name, const Math::Vec4& vec4);
    void SetUniformVec4Array(unsigned int& shader, const char* name, int size, const float* data);
    void SetUniformBool(unsigned int& shader, const char* name, bool value);
    void SetUniformBoolArray(unsigned int& shader, const char* name, int size,const bool* data);
    void SetUniformMatrix4f(unsigned int& shader, const char* name, const Math::Mat4& mat);
}