#pragma once
#include "../Core/Core.h"
#include <map>
#include "../GL/GLTexture/GLTexture.h"
namespace Fusion{
    class FUSION_API TextureList{
    public:
        TextureList() = default;
        void AddTexture(const char* path,const char* name,bool dynamic);
        GL::TextureData* GetTexture(const char* name);
        void Reset(bool total);
    private:
        std::map<std::string, GL::TextureData*> m_DynamicTextures;
        std::map<std::string, GL::TextureData*> m_StaticTextures;
    };
}
