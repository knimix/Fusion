#pragma once
#include <cstdint>
#include <array>
#include <Math/Vector/Vec2/Vec2.h>
#include <Math/Vector/Vec4/Vec4.h>
#include <Math/Matrix/Mat4/Mat4.h>
#include "../IO/IO.h"
#include "../GL/GLTexture/GLTexture.h"
#include "../Font/Font.h"
#define FUSION_TEXT_ARRANGEMENT_CENTERED 1
#define FUSION_TEXT_ARRANGEMENT_LEFT 0
#define FUSION_TEXT_ARRANGEMENT_RIGHT 2
namespace Fusion{
    class Renderer2D {
    public:
        static const size_t MaxQuadCount = 1000;
        static const size_t MaxVertexCount = MaxQuadCount * 4;
        static const size_t MaxIndexCount = MaxQuadCount * 6;
        static const size_t MaxTextures = 16;
        explicit Renderer2D(IO* io);
        ~Renderer2D();
        void BeginBatch();
        void EndBatch();
        void Flush();
        void DrawQuad(const Math::Vec2& position, const Math::Vec2& size, const Math::Vec4& color, const Math::Vec4& radius, float borderThickness, const Math::Vec4& borderColor, GL::TextureData* textureData = nullptr, bool decorated = true);
        void DrawLine(const Math::Vec2& pointA, const Math::Vec2& pointB, float thickness, const Math::Vec4& color);
        void DrawString(const char* text,const Font* font, const Math::Vec2& position, const Math::Vec2& size, const Math::Vec4& color, int textArrangement = FUSION_TEXT_ARRANGEMENT_CENTERED);
    private:
        struct Vertex {
            Math::Vec2 Position;
            Math::Vec2 TextureCoord;
            float TextureIndex;
            float QuadID;
        };
        unsigned int m_QuadVA = 0;
        unsigned int m_QuadVB = 0;
        unsigned int m_QuadIB = 0;
        unsigned int m_QuadShader = 0;

        Vertex* m_QuadBuffer = nullptr;
        Vertex* m_QuadBufferPtr = nullptr;

        unsigned int m_QuadCount = 0;

        std::array<Math::Vec4,MaxQuadCount> m_QuadColor{};
        std::array<Math::Vec4,MaxQuadCount> m_QuadBorderColor{};
        std::array<float,MaxQuadCount> m_QuadBorderThickness{};
        std::array<Math::Vec4,MaxQuadCount> m_QuadCornerRadius{};
        std::array<Math::Vec2,MaxQuadCount> m_QuadPosition{};
        std::array<Math::Vec2,MaxQuadCount> m_QuadSize{};
        std::array<int,MaxQuadCount> m_QuadDecoration{};
        std::array<Math::Vec4,MaxQuadCount> m_QuadCutoff{};

        uint32_t m_IndexCount = 0;

        std::array<uint32_t, MaxTextures> m_TextureSlots{};
        uint32_t m_TextureSlotIndex = 0;

        IO* m_IO;
        Math::Mat4 m_Ortho;
    };
}
