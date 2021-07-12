#pragma once
#include "../Core/Core.h"
#include "../Libraries/STB/include/STB/stb_truetype.h"
namespace Fusion{
    class FUSION_API Font {
    public:
        Font(const char* path, int size);
        ~Font();
        inline const int GetFontSize() const{return m_FontSize;}
        inline const stbtt_packedchar * GetFontData() const {return m_FontData;}
        inline const stbtt_fontinfo* GetFontInfo() const {return m_FontInfo;}
        inline const unsigned int GetFontTexture() const {return m_FontTexture;}
    private:
        const char* m_Path = nullptr;
        int m_FontSize = 0;
        stbtt_packedchar*  m_FontData = nullptr;
        stbtt_fontinfo* m_FontInfo = nullptr;
        unsigned int m_FontTexture = 0;
    };

}