#pragma once

#include "../../Core/Core.h"
#include "../../WindowManager/WindowManager.h"

namespace Fusion {
    class FUSION_API Button : public Fusion::Component {
    public:
        Button() = default;
        ~Button() override;
        const char* m_Window = nullptr;
        const char* m_Name = nullptr;
        void SetText(const char* text);
        void SetFont(const Font* font);
        void SetTextOffset(const Math::Vec2& offset);
        void SetTexture(GL::TextureData* texture);
        void SetIcon(GL::TextureData* icon);
        void SetIconSize(const Math::Vec2& size);
        void SetIconOffset(const Math::Vec2& offset);
        void SetCorners(const Math::Vec4& corners);
        void SetBorderThickness(float thickness);
        void SetPosition(const Math::Vec2& position);
        void SetSize(const Math::Vec2& size);
        void SetBaseColor(const Math::Vec4& color);
        void SetHoverColor(const Math::Vec4& color);
        void SetClickColor(const Math::Vec4& color);
        void SetBorderBaseColor(const Math::Vec4& color);
        void SetBorderHoverColor(const Math::Vec4& color);
        void SetBorderClickColor(const Math::Vec4& color);
        void SetTextBaseColor(const Math::Vec4& color);
        void SetTextHoverColor(const Math::Vec4& color);
        void SetTextClickColor(const Math::Vec4& color);
        void SetHoverCallback(void (*callback)());
        void SetClickCallback(void (*callback)());
        void SetPressCallback(void (*callback)());
    private:
        void Update(const Fusion::IO* io, bool& onInput) override;
        void Render(Renderer2D* renderer) override;
        bool m_Clicked = true;
        const char* m_Text = nullptr;
        const Font* m_Font = nullptr;
        Math::Vec2 m_TextOffset = {0,0};
        GL::TextureData* m_Texture = nullptr;
        GL::TextureData* m_Icon = nullptr;
        Math::Vec2 m_IconSize = {16, 16};
        Math::Vec2 m_IconOffset = {0, 0};
        Math::Vec4 m_Corners = {0.0, 0.0, 0.0, 0.0};
        float m_BorderThickness = 0;
        Math::Vec2 m_Position = {0, 0};
        Math::Vec2 m_Size = {100, 40};
        Math::Vec4 m_BaseColor = {0.8, 0.2, 0.2, 1.0};
        Math::Vec4 m_HoverColor = {-1, -1, -1, -1};
        Math::Vec4 m_ClickColor = {-1, -1, -1, -1};
        Math::Vec4 m_BorderBaseColor = {0.0, 0.0, 0.0, 0.0};
        Math::Vec4 m_BorderHoverColor = {-1, -1, -1, -1};
        Math::Vec4 m_BorderClickColor = {-1, -1, -1, -1};
        Math::Vec4 m_TextBaseColor = {1.0, 1.0, 1.0, 1.0};
        Math::Vec4 m_TextHoverColor = {-1, -1, -1, -1};
        Math::Vec4 m_TextClickColor = {-1, -1, -1, -1};
        Math::Vec4 m_CurrentColor = {0.8, 0.2, 0.2, 1.0};
        Math::Vec4 m_CurrentBorderColor = {0.8, 0.8, 0.8, 1.0};
        Math::Vec4 m_CurrentTextColor = {1.0, 1.0, 1.0, 1.0};
        void (*m_HoverCallback)() = nullptr;
        void (*m_ClickCallback)() = nullptr;
        void (*m_PressCallback)() = nullptr;
    };
    void AddButton(const char* name, bool dynamic, const char* window, uint8_t componentList = FUSION_COMPONENT_LIST_MAIN);
    Button* GetButton(const char* name, const char* window);
}