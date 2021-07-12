#pragma once
#include "../Font/Font.h"
#include <map>
namespace Fusion{
    class FUSION_API FontList {
    public:
        FontList() = default;
        void AddFont(Font* font,const char* name,bool dynamic);
        Font* GetFont(const char* name);
        void Reset(bool total);
    private:
        std::map<std::string, Font*> m_DynamicFonts;
        std::map<std::string, Font*> m_StaticFonts;
    };
}
