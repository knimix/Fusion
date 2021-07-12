#include "GLBuffer.h"

void Fusion::GL::CreateVertexArray(unsigned int& va) {
    glGenVertexArrays(1, &va);
}
void Fusion::GL::DeleteVertexArray(unsigned int& va) {
    glDeleteVertexArrays(1, &va);
    va = 0;
}
void Fusion::GL::BindVertexArray(unsigned int& va) {
    glBindVertexArray(va);
}
void Fusion::GL::UnbindVertexArray(unsigned int& va) {
    glBindVertexArray(0);
    va = 0;
}
void Fusion::GL::CreateVertexBuffer(unsigned int& vb) {
    glGenBuffers(1, &vb);
}
void Fusion::GL::DeleteVertexBuffer(unsigned int& vb) {
    glDeleteBuffers(1, &vb);
    vb = 0;
}
void Fusion::GL::BindVertexBuffer(unsigned int& vb) {
    glBindBuffer(GL_ARRAY_BUFFER, vb);
}
void Fusion::GL::UnbindVertexBuffer(unsigned int& vb) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Fusion::GL::VertexBufferData(const void* data, uint64_t size, unsigned int drawMode) {
    glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
}
void Fusion::GL::VertexBufferSubData(const void* data, uint64_t size, unsigned int offset) {
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
void Fusion::GL::ConfigureVertexBuffer(unsigned int index, GLenum type, unsigned int count, unsigned int stride, unsigned int& offset) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, count, type, GL_FALSE, stride, reinterpret_cast<const void*>(offset));
    offset += GetSizeFromType(type) * count;
}
unsigned int Fusion::GL::GetSizeFromType(GLenum type) {
    switch (type) {
        case GL_FLOAT:
            return sizeof(float);
        case GL_DOUBLE:
            return sizeof(double);
        case GL_INT:
            return sizeof(int);
        case GL_BOOL:
            return sizeof(bool);
        default:
            return sizeof(float);
    }
}
void Fusion::GL::CreateIndexBuffer(unsigned int& ib) {
    glGenBuffers(1, &ib);
}
void Fusion::GL::DeleteIndexBuffer(unsigned int& ib) {
    glDeleteBuffers(1, &ib);
    ib = 0;
}
void Fusion::GL::BindIndexBuffer(unsigned int& ib) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
}
void Fusion::GL::UnbindIndexBuffer(unsigned int& ib) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Fusion::GL::IndexBufferData(const void* data, uint64_t size, unsigned int drawMode) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawMode);
}
