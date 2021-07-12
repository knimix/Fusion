#pragma once
#include "../GLCore.h"
namespace Fusion::GL{
    void CreateVertexArray(unsigned int& va);
    void DeleteVertexArray(unsigned int& va);
    void BindVertexArray(unsigned int& va);
    void UnbindVertexArray(unsigned int& va);
    void CreateVertexBuffer(unsigned int& vb);
    void DeleteVertexBuffer(unsigned int& vb);
    void BindVertexBuffer(unsigned int& vb);
    void UnbindVertexBuffer(unsigned int& vb);
    void VertexBufferData(const void* data, uint64_t size, unsigned int drawMode);
    void VertexBufferSubData(const void* data, uint64_t size, unsigned int offset);
    void ConfigureVertexBuffer(unsigned int index, GLenum type, unsigned int count, unsigned int stride, unsigned int& offset);
    unsigned int GetSizeFromType(GLenum type);
    void CreateIndexBuffer(unsigned int& ib);
    void DeleteIndexBuffer(unsigned int& ib);
    void BindIndexBuffer(unsigned int& ib);
    void UnbindIndexBuffer(unsigned int& ib);
    void IndexBufferData(const void* data, uint64_t size, unsigned int drawMode);
}