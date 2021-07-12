#include "Renderer2D.h"
#include "../GL/GLBuffer/GLBuffer.h"
#include "../GL/GLShader/GLShader.h"
#include <Math/Trigonometry/Trigonometry.h>
#include <cmath>
#include <cstring>

struct AlignedQuad {
    Math::Vec2 qX;
    Math::Vec2 qY;
    Math::Vec2 qS;
    Math::Vec2 qT;
};
Fusion::Renderer2D::Renderer2D(Fusion::IO* io) {
    m_IO = io;
    m_QuadBuffer = new Vertex[MaxVertexCount];
    GL::CreateVertexArray(m_QuadVA);
    GL::BindVertexArray(m_QuadVA);
    GL::CreateVertexBuffer(m_QuadVB);
    GL::BindVertexBuffer(m_QuadVB);
    unsigned int offset = 0;
    GL::ConfigureVertexBuffer(0, GL_FLOAT, 2, sizeof(Vertex), offset);
    GL::ConfigureVertexBuffer(1, GL_FLOAT, 2, sizeof(Vertex), offset);
    GL::ConfigureVertexBuffer(2, GL_FLOAT, 1, sizeof(Vertex), offset);
    GL::ConfigureVertexBuffer(3, GL_FLOAT, 1, sizeof(Vertex), offset);
    GL::VertexBufferData(nullptr, MaxVertexCount * sizeof(Vertex), GL_DYNAMIC_DRAW);
    uint32_t indices[MaxIndexCount];
    uint32_t indexOffset = 0;
    for (int i = 0; i < MaxIndexCount; i += 6) {
        indices[i + 0] = 0 + indexOffset;
        indices[i + 1] = 1 + indexOffset;
        indices[i + 2] = 2 + indexOffset;
        indices[i + 3] = 2 + indexOffset;
        indices[i + 4] = 1 + indexOffset;
        indices[i + 5] = 3 + indexOffset;
        indexOffset += 4;
    }
    GL::CreateIndexBuffer(m_QuadIB);
    GL::BindIndexBuffer(m_QuadIB);
    GL::IndexBufferData(indices, sizeof(indices), GL_DYNAMIC_DRAW);
    for (size_t i = 0; i < MaxTextures; i++) {
        m_TextureSlots[i] = 0;
    }
    GL::CreateShader("../../../../Fusion/Shader/Vertex.glsl", "../../../../Fusion/Shader/Fragment.glsl", m_QuadShader);
    GL::BindShader(m_QuadShader);
    GL::SetUniformInt(m_QuadShader, "F_Texture0", 0);
    GL::SetUniformInt(m_QuadShader, "F_Texture1", 1);
    GL::SetUniformInt(m_QuadShader, "F_Texture2", 2);
    GL::SetUniformInt(m_QuadShader, "F_Texture3", 3);
    GL::SetUniformInt(m_QuadShader, "F_Texture4", 4);
    GL::SetUniformInt(m_QuadShader, "F_Texture5", 5);
    GL::SetUniformInt(m_QuadShader, "F_Texture6", 6);
    GL::SetUniformInt(m_QuadShader, "F_Texture7", 7);
    GL::SetUniformInt(m_QuadShader, "F_Texture8", 8);
    GL::SetUniformInt(m_QuadShader, "F_Texture9", 9);
    GL::SetUniformInt(m_QuadShader, "F_Texture10", 10);
    GL::SetUniformInt(m_QuadShader, "F_Texture11", 11);
    GL::SetUniformInt(m_QuadShader, "F_Texture12", 12);
    GL::SetUniformInt(m_QuadShader, "F_Texture13", 13);
    GL::SetUniformInt(m_QuadShader, "F_Texture14", 14);
    GL::SetUniformInt(m_QuadShader, "F_Texture15", 15);
    m_Ortho = Math::Ortho((float) 0.0f, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight, (float) 0.0f, -1.0f, 1.0f);
    GL::SetUniformMatrix4f(m_QuadShader, "V_Ortho", m_Ortho);
    GL::SetUniformVec2(m_QuadShader, "F_ScreenResolution", {(float) m_IO->WindowWidth, (float) m_IO->WindowHeight});
}
Fusion::Renderer2D::~Renderer2D() {
    GL::DeleteVertexArray(m_QuadVA);
    GL::DeleteVertexBuffer(m_QuadVB);
    GL::DeleteIndexBuffer(m_QuadIB);
    delete[] m_QuadBuffer;
}
void Fusion::Renderer2D::BeginBatch() {
    m_QuadBufferPtr = m_QuadBuffer;
}
void Fusion::Renderer2D::EndBatch() {
    GLsizeiptr size = (uint8_t*) m_QuadBufferPtr - (uint8_t*) m_QuadBuffer;
    GL::BindVertexBuffer(m_QuadVB);
    glBufferSubData(GL_ARRAY_BUFFER, 0,size, m_QuadBuffer);
}
void Fusion::Renderer2D::Flush() {
    GL::BindShader(m_QuadShader);
    for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
        glBindTextureUnit(i, m_TextureSlots[i]);
    }
    if (m_IO->OnWindowResize) {
        m_Ortho = Math::Ortho((float) 0.0f, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight, (float) 0.0f, -1.0f, 1.0f);
        GL::SetUniformMatrix4f(m_QuadShader, "V_Ortho", m_Ortho);
        GL::SetUniformVec2(m_QuadShader, "F_ScreenResolution", {(float) m_IO->WindowWidth, (float) m_IO->WindowHeight});
    }
    GL::SetUniformVec4Array(m_QuadShader, "F_QuadColor", MaxQuadCount, (float*) m_QuadColor.data());
    GL::SetUniformVec4Array(m_QuadShader, "F_QuadBorderColor", MaxQuadCount, (float*) m_QuadBorderColor.data());
    GL::SetUniformFloatArray(m_QuadShader, "F_QuadBorderThickness", MaxQuadCount, (float*) m_QuadBorderThickness.data());
    GL::SetUniformVec4Array(m_QuadShader, "F_QuadCornerRadius", MaxQuadCount, (float*) m_QuadCornerRadius.data());
    GL::SetUniformVec2Array(m_QuadShader, "F_QuadPosition", MaxQuadCount, (float*) m_QuadPosition.data());
    GL::SetUniformVec2Array(m_QuadShader, "F_QuadSize", MaxQuadCount, (float*) m_QuadSize.data());
    GL::SetUniformIntArray(m_QuadShader, "F_QuadDecoration", MaxQuadCount, (int*) m_QuadDecoration.data());
    GL::SetUniformVec4Array(m_QuadShader, "F_QuadCutoff", MaxQuadCount, (float*) m_QuadCutoff.data());
    GL::BindVertexArray(m_QuadVA);
   glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
    m_QuadCount = 0;
    m_QuadColor = {};
    m_QuadBorderColor = {};
    m_QuadBorderThickness = {};
    m_QuadCornerRadius = {};
    m_QuadPosition = {};
    m_QuadSize = {};
    m_TextureSlotIndex = 0;
    m_IndexCount = 0;
}
void Fusion::Renderer2D::DrawQuad(const Math::Vec2& position, const Math::Vec2& size, const Math::Vec4& color, const Math::Vec4& radius, float borderThickness, const Math::Vec4& borderColor, GL::TextureData* textureData, bool decorated) {
    if (m_IndexCount + 6 >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    int textureIndex = -1;
    if (textureData != nullptr) {
        if (textureData->Data != nullptr) {
            for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
                if (m_TextureSlots[i] == textureData->TextureID) {
                    textureIndex = i;
                    break;
                }
            }
            if (textureIndex == -1) {
                textureIndex = m_TextureSlotIndex;
                m_TextureSlots[m_TextureSlotIndex] = textureData->TextureID;
                m_TextureSlotIndex++;
            }
        }
    }
    m_QuadBufferPtr->Position = {position.x, position.y};
    m_QuadBufferPtr->TextureCoord = {0.0f, 0.0f};
    m_QuadBufferPtr->TextureIndex = (float) textureIndex;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoord = {0.0f, 1.0f};
    m_QuadBufferPtr->TextureIndex = (float) textureIndex;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y};
    m_QuadBufferPtr->TextureCoord = {1.0f, 0.0f};
    m_QuadBufferPtr->TextureIndex = (float) textureIndex;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoord = {1.0f, 1.0f};
    m_QuadBufferPtr->TextureIndex = (float) textureIndex;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadColor[m_QuadCount] = color;
    m_QuadBorderColor[m_QuadCount] = borderColor;
    m_QuadBorderThickness[m_QuadCount] = borderThickness;
    m_QuadCornerRadius[m_QuadCount] = radius;
    m_QuadPosition[m_QuadCount] = position;
    m_QuadSize[m_QuadCount] = size;
    m_QuadDecoration[m_QuadCount] = decorated;
    m_QuadCutoff[m_QuadCount] = {0, 0, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight};
    m_IndexCount += 6;
    m_QuadCount++;
}
void Fusion::Renderer2D::DrawLine(const Math::Vec2& pointA, const Math::Vec2& pointB, float thickness, const Math::Vec4& color) {
    if (m_IndexCount + 6 >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    double angle = Math::ToDegrees(std::atan2(pointA.y - pointB.y, pointA.x - pointB.x));
    angle += 90.0;
    double radius = thickness / 2;
    m_QuadBufferPtr->Position = {static_cast<float>((float) pointA.x + (-Math::Cos(angle) * radius)), static_cast<float>((float) pointA.y + (-Math::Sin(angle) * radius))};
    m_QuadBufferPtr->TextureCoord = {0.0f, 0.0f};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {static_cast<float>(pointA.x + (Math::Cos(angle) * radius)), static_cast<float>(pointA.y + (Math::Sin(angle) * radius))};
    m_QuadBufferPtr->TextureCoord = {1.0f, 0.0f};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {static_cast<float>(pointB.x + (-Math::Cos(angle) * radius)), static_cast<float>(pointB.y + (-Math::Sin(angle) * radius))};
    m_QuadBufferPtr->TextureCoord = {1.0f, 1.0f};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {static_cast<float>(pointB.x + (Math::Cos(angle) * radius)), static_cast<float>(pointB.y + (Math::Sin(angle) * radius))};
    m_QuadBufferPtr->TextureCoord = {0.0f, 1.0f};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->QuadID = (float) m_QuadCount;
    m_QuadBufferPtr++;
    m_QuadColor[m_QuadCount] = color;
    m_QuadBorderColor[m_QuadCount] = {0.0f, 0.0f, 0.0f, 0.0f};
    m_QuadBorderThickness[m_QuadCount] = 0.0f;
    m_QuadCornerRadius[m_QuadCount] = {0.0f, 0.0f, 0.0f, 0.0f};
    m_QuadPosition[m_QuadCount] = {0.0f, 0.0f};
    m_QuadSize[m_QuadCount] = {0.0f, 0.0f};
    m_QuadDecoration[m_QuadCount] = false;
    m_QuadCutoff[m_QuadCount] = {0, 0, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight};
    m_IndexCount += 6;
    m_QuadCount++;
}
void Fusion::Renderer2D::DrawString(const char* text,const Fusion::Font* font, const Math::Vec2& position, const Math::Vec2& size, const Math::Vec4& color, int textArrangement) {
    if (text == nullptr) {
        return;
    }
    if (font == nullptr) {
        return;
    }
    if (size.y < ((float) font->GetFontSize())) {
        return;
    }
    uint32_t textLength = strlen(text);
    if ((m_IndexCount + 6) * textLength >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    int textureIndex = -1;
    for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
        if (m_TextureSlots[i] == font->GetFontTexture()) {
            textureIndex = i;
            break;
        }
    }
    if (textureIndex == -1) {
        textureIndex = m_TextureSlotIndex;
        m_TextureSlots[m_TextureSlotIndex] = font->GetFontTexture();
        m_TextureSlotIndex++;
    }
    float cursorX = 0;
    float cursorY = 0;
    std::vector<AlignedQuad> characters;
    for (int i = 0; i < textLength; i++) {
        char character = text[i];
        if (character >= 32 && character < 128) {
            stbtt_aligned_quad q;
            stbtt_GetPackedQuad(font->GetFontData(), 1024, 1024, character - 32, &cursorX, &cursorY, &q, 1);
            AlignedQuad quad{};
            quad.qX = {q.x0, q.x1};
            quad.qY = {q.y0, q.y1};
            quad.qS = {q.s0, q.s1};
            quad.qT = {q.t0, q.t1};
            if (cursorX > size.x) {
                cursorX -= q.x1 - q.x0;
                break;
            }
            characters.emplace_back(quad);
        }
    }
    float height = (float) font->GetFontData()['H' - 32].y1 - (float) font->GetFontData()['H' - 32].y0;
    height -= height / 2;
    float x = 0;
    float y = size.y / 2 + height / 2;
    if (textArrangement == FUSION_TEXT_ARRANGEMENT_LEFT) {
        x = 0;
    } else if (textArrangement == FUSION_TEXT_ARRANGEMENT_RIGHT) {
        x = (size.x - cursorX);
    } else if (textArrangement == FUSION_TEXT_ARRANGEMENT_CENTERED) {
        x = (size.x - cursorX) / 2;
    }
    for (AlignedQuad quad : characters) {
        m_QuadBufferPtr->Position = {quad.qX.x + position.x + x, quad.qY.y + position.y + y};
        m_QuadBufferPtr->TextureCoord = {quad.qS.x, quad.qT.y};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->QuadID = (float) m_QuadCount;
        m_QuadBufferPtr++;
        m_QuadBufferPtr->Position = {quad.qX.x + position.x + x, quad.qY.x + position.y + y};
        m_QuadBufferPtr->TextureCoord = {quad.qS.x, quad.qT.x};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->QuadID = (float) m_QuadCount;
        m_QuadBufferPtr++;
        m_QuadBufferPtr->Position = {quad.qX.y + position.x + x, quad.qY.y + position.y + y};
        m_QuadBufferPtr->TextureCoord = {quad.qS.y, quad.qT.y};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->QuadID = (float) m_QuadCount;
        m_QuadBufferPtr++;
        m_QuadBufferPtr->Position = {quad.qX.y + position.x + x, quad.qY.x + position.y + y};
        m_QuadBufferPtr->TextureCoord = {quad.qS.y, quad.qT.x};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->QuadID = (float) m_QuadCount;
        m_QuadBufferPtr++;
        m_QuadColor[m_QuadCount] = color;
        m_QuadBorderColor[m_QuadCount] = {0.0f, 0.0f, 0.0f, 0.0f};
        m_QuadBorderThickness[m_QuadCount] = 0;
        m_QuadCornerRadius[m_QuadCount] = {0.0f, 0.0f, 0.0f, 0.0f};
        m_QuadPosition[m_QuadCount] = position;
        m_QuadSize[m_QuadCount] = size;
        m_QuadDecoration[m_QuadCount] = false;
        m_QuadCutoff[m_QuadCount] = {0, 0, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight};
        m_IndexCount += 6;
        m_QuadCount++;
    }
}