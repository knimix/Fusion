#pragma once
#include <cstdint>
namespace Fusion::GL{
    struct TextureData {
        unsigned int TextureID;
        uint8_t* Data = nullptr;
        int Width = 0, Height = 0, Channels = 0;
    };
    void LoadTexture(const char* path, TextureData& textureData);
    void UnloadTexture(uint8_t* data);
    void CreateTexture(TextureData& textureData);
    void DeleteTexture(unsigned int& texture);
    void BindTexture(unsigned int& texture);
    void UnbindTexture();
}