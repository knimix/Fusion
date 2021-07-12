#include "GLShader.h"
#include "../GLCore.h"
#include <fstream>
#include <iostream>

static void LoadShader(const char* path, std::string& source) {
    std::ifstream file(path);
    std::string line;
    source.clear();
    if (file.is_open()) {
        while (std::getline(file, line)) {
            source += line + '\n';
        }
    }
}
static void CompileShader(unsigned int type, std::string& source, unsigned int& id) {
    id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message << std::endl;
    }
}
void Fusion::GL::CreateShader(const char* vertex, const char* fragment, unsigned int& shader) {
    shader = glCreateProgram();
    BindShader(shader);
    unsigned int vs = -1;
    unsigned int fs = -1;
    std::string vertexSource;
    std::string fragmentSource;
    LoadShader(vertex, vertexSource);
    LoadShader(fragment, fragmentSource);
    CompileShader(GL_VERTEX_SHADER, vertexSource, vs);
    CompileShader(GL_FRAGMENT_SHADER, fragmentSource, fs);
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glValidateProgram(shader);
    glDeleteShader(vs);
    glDeleteShader(fs);
}
void Fusion::GL::BindShader(unsigned int& shader) {
    glUseProgram(shader);
}
void Fusion::GL::UnbindShader(unsigned int& shader) {
    glUseProgram(0);
}
void Fusion::GL::SetUniformInt(unsigned int& shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader, name), value);
}
void Fusion::GL::SetUniformIntArray(unsigned int& shader, const char* name, int size, const int* data) {
    glUniform1iv(glGetUniformLocation(shader, name), size, data);
}
void Fusion::GL::SetUniformFloat(unsigned int& shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader, name), value);
}
void Fusion::GL::SetUniformFloatArray(unsigned int& shader, const char* name, int size, const float* data) {
    glUniform1fv(glGetUniformLocation(shader, name), size, data);
}
void Fusion::GL::SetUniformVec2(unsigned int& shader, const char* name, const Math::Vec2& vec2) {
    glUniform2f(glGetUniformLocation(shader, name), vec2.x, vec2.y);
}
void Fusion::GL::SetUniformVec2Array(unsigned int& shader, const char* name, int size, const float* data) {
    glUniform2fv(glGetUniformLocation(shader, name), size, data);
}
void Fusion::GL::SetUniformVec3(unsigned int& shader, const char* name, const Math::Vec3& vec3) {
    glUniform3f(glGetUniformLocation(shader, name), vec3.x, vec3.y, vec3.z);
}
void Fusion::GL::SetUniformVec3Array(unsigned int& shader, const char* name, int size, const float* data) {
    glUniform3fv(glGetUniformLocation(shader, name), size, data);
}
void Fusion::GL::SetUniformVec4(unsigned int& shader, const char* name, const Math::Vec4& vec4) {
    glUniform4f(glGetUniformLocation(shader, name), vec4.x, vec4.y, vec4.z, vec4.w);
}
void Fusion::GL::SetUniformVec4Array(unsigned int& shader, const char* name, int size, const float* data) {
    glUniform4fv(glGetUniformLocation(shader, name), size, data);
}
void Fusion::GL::SetUniformBool(unsigned int& shader, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(shader, name), (GLint) value);
}
void Fusion::GL::SetUniformBoolArray(unsigned int& shader, const char* name, int size, const bool* data) {
    glUniform1iv(glGetUniformLocation(shader, name), size, (GLint*) data);
}
void Fusion::GL::SetUniformMatrix4f(unsigned int& shader, const char* name, const Math::Mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, (GLfloat*) (&matrix));
}