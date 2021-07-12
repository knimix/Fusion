#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../GLCore.h"
#include <STB/stb_image.h>
#include <iostream>

void Fusion::GL::LoadTexture(const char* path, TextureData& textureData) {
    textureData.Data = stbi_load(path, &textureData.Width, &textureData.Height, &textureData.Channels, 0);
}
void Fusion::GL::UnloadTexture(uint8_t* data) {
    stbi_image_free(data);
}
void Fusion::GL::CreateTexture(TextureData& textureData) {
    if (textureData.Data == nullptr) {
        return;
    }
    auto format = GL_RGB;
    if (textureData.Channels == 1) {
        format = GL_RED;
    } else if (textureData.Channels == 3) {
        format = GL_RGB;
    } else if (textureData.Channels == 4) {
        format = GL_RGBA;
    }
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, textureData.Width, textureData.Height, 0, format, GL_UNSIGNED_BYTE, textureData.Data);
    textureData.TextureID = texture;
    std::cout << "Texture-ID: "<< texture << std::endl;
}
void Fusion::GL::DeleteTexture(unsigned int& texture) {
    glDeleteTextures(1, &texture);
}
void Fusion::GL::BindTexture(unsigned int& texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
}
void Fusion::GL::UnbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
