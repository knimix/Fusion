#pragma once
#include "../../Core/Core.h"
#include "../../WindowManager/WindowManager.h"
namespace Fusion{
    class FUSION_API Button : public Fusion::Component{
    public:
        Button() = default;
        ~Button() override;
        void Update(const Fusion::IO* io,bool& onInput) override;
        void Render(Renderer2D* renderer) override;

        const char* m_ButtonText = nullptr;
        Font* m_ButtonTextFont = nullptr;

        GL::TextureData* m_ButtonTexture = nullptr;

        GL::TextureData* m_ButtonIcon = nullptr;
        Math::Vec2 m_ButtonIconOffset = {0,0};

        Math::Vec2 m_Position = {0,0};
        Math::Vec2 m_Size = {100,40};

        Math::Vec4 m_BaseColor = {0.6,0.2,0.2,1.0};
        Math::Vec4 m_HoverColor = {0.6,0.3,0.3,1.0};
        Math::Vec4 m_ClickColor = {0.6,0.4,0.4,1.0};

        Math::Vec4 m_BorderBaseColor = {0.6,0.2,0.2,1.0};
        Math::Vec4 m_BorderHoverColor = {0.6,0.2,0.2,1.0};
        Math::Vec4 m_BorderClickColor = {0.6,0.2,0.2,1.0};

        Math::Vec4 m_TextBaseColor = {0.6,0.2,0.2,1.0};
        Math::Vec4 m_TextHoverColor = {0.6,0.2,0.2,1.0};
        Math::Vec4 m_TextClickColor = {0.6,0.2,0.2,1.0};

        Math::Vec4 m_CurrentButtonColor = {};
        Math::Vec4 m_CurrentBorderColor = {};
        Math::Vec4 m_CurrentTextColor = {};
    };
    void AddButton(const char* name, bool dynamic, const char* window, uint8_t componentList = FUSION_COMPONENT_LIST_MAIN);
    void SetButtonPosition(const char* name,const char* window,const Math::Vec2& position);
    void SetButtonSize(const char* name,const char* window, const Math::Vec2& size);
    void SetButtonBaseColor(const char* name,const char* window, const Math::Vec4& color);
    void SetButtonHoverColor(const char* name,const char* window, const Math::Vec4& color);
    void SetButtonClickColor(const char* name,const char* window, const Math::Vec4& color);

}