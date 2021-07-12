#include "FontList.h"

void Fusion::FontList::AddFont(Fusion::Font* font, const char* name, bool dynamic) {
    if(m_DynamicFonts.count(name) || m_StaticFonts.count(name)){
        delete font;
        return;
    }
    if(dynamic){
        m_DynamicFonts.emplace(std::pair<std::string,Font*>(name,font));
    }else{
        m_StaticFonts.emplace(std::pair<std::string,Font*>(name,font));
    }
}
Fusion::Font* Fusion::FontList::GetFont(const char* name) {
    if(m_DynamicFonts.count(name)){
        return m_DynamicFonts.at(name);
    }
    if(m_StaticFonts.count(name)){
        return m_StaticFonts.at(name);
    }
    return nullptr;
}
void Fusion::FontList::Reset(bool total) {
    if(total){
        std::map<std::string, Font*>::iterator it;
        for (it = m_DynamicFonts.begin(); it != m_DynamicFonts.end(); it++) {
            delete it->second;
        }
        for (it = m_StaticFonts.begin(); it != m_StaticFonts.end(); it++) {
            delete it->second;
        }
        m_DynamicFonts.clear();
        m_StaticFonts.clear();
    }else{
        std::map<std::string, Font*>::iterator it;
        for (it = m_DynamicFonts.begin(); it != m_DynamicFonts.end(); it++) {
            delete it->second;
        }
        m_DynamicFonts.clear();
    }
}
