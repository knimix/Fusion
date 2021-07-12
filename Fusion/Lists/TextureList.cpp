#include "TextureList.h"
#include <string>
void Fusion::TextureList::AddTexture(const char* path, const char* name, bool dynamic) {
    if(m_DynamicTextures.count(name) || m_StaticTextures.count(name)){
        return;
    }
    auto textureData = new GL::TextureData;
    GL::LoadTexture(path,*textureData);
    if(textureData->Data == nullptr){
        delete textureData;
        return;
    }
    GL::CreateTexture(*textureData);
    if(dynamic){
        m_DynamicTextures.emplace(std::pair<std::string,GL::TextureData*>(name,textureData));
    }else{
        m_StaticTextures.emplace(std::pair<std::string,GL::TextureData*>(name,textureData));
    }
}
Fusion::GL::TextureData* Fusion::TextureList::GetTexture(const char* name) {
    if(m_DynamicTextures.count(name)){
        return m_DynamicTextures.at(name);
    }
    if(m_StaticTextures.count(name)){
        return m_StaticTextures.at(name);
    }
    return nullptr;
}
void Fusion::TextureList::Reset(bool total) {
    if(total){
        std::map<std::string, GL::TextureData*>::iterator it;
        for (it = m_DynamicTextures.begin(); it != m_DynamicTextures.end(); it++) {
            GL::UnloadTexture(it->second->Data);
            GL::DeleteTexture(it->second->TextureID);
            delete it->second;
        }
        for (it = m_StaticTextures.begin(); it != m_StaticTextures.end(); it++) {
            GL::UnloadTexture(it->second->Data);
            GL::DeleteTexture(it->second->TextureID);
            delete it->second;
        }
        m_DynamicTextures.clear();
        m_StaticTextures.clear();
    }else{
        std::map<std::string, GL::TextureData*>::iterator it;
        for (it = m_DynamicTextures.begin(); it != m_DynamicTextures.end(); it++) {
            GL::UnloadTexture(it->second->Data);
            GL::DeleteTexture(it->second->TextureID);
            delete it->second;
        }
        m_DynamicTextures.clear();
    }
}
