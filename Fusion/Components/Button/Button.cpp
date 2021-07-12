#include "Button.h"

Fusion::Button::~Button() {
}
void Fusion::Button::Update(const Fusion::IO* io, bool& onInput) {
    if (io->MouseX >= m_Position.x && io->MouseX <= m_Position.x + m_Size.x && io->MouseY >= m_Position.y && io->MouseY <= m_Position.y + m_Size.y) {
        if (io->Mouse[FUSION_MOUSE_BUTTON_1]) {
            if(!m_Clicked){
                m_Clicked = true;
                if(m_ClickCallback != nullptr){
                    m_ClickCallback();
                }
                if (m_CurrentColor != m_ClickColor && m_ClickColor.x != -1 && m_ClickColor.y != -1 && m_ClickColor.z != -1 && m_ClickColor.w != -1) {
                    m_CurrentColor = m_ClickColor;
                    onInput = true;
                    Fusion::UpdateWindow(GetCurrentWindow());
                }
            }
            if (m_CurrentBorderColor != m_BorderClickColor && m_BorderClickColor.x != -1 && m_BorderClickColor.y != -1 && m_BorderClickColor.z != -1 && m_BorderClickColor.w != -1) {
                m_CurrentBorderColor = m_BorderClickColor;
                onInput = true;
                Fusion::UpdateWindow(GetCurrentWindow());
            }
            if (m_CurrentTextColor != m_TextClickColor && m_TextClickColor.x != -1 && m_TextClickColor.y != -1 && m_TextClickColor.z != -1 && m_TextClickColor.w != -1) {
                m_CurrentTextColor = m_TextClickColor;
                onInput = true;
                Fusion::UpdateWindow(GetCurrentWindow());
            }
            if(m_PressCallback != nullptr){
                m_PressCallback();
            }
        } else {
            if (m_CurrentColor != m_HoverColor && m_HoverColor.x != -1 && m_HoverColor.y != -1 && m_HoverColor.z != -1 && m_HoverColor.w != -1) {
                m_CurrentColor = m_HoverColor;
                onInput = true;
                Fusion::UpdateWindow(GetCurrentWindow());
            }
            if (m_CurrentBorderColor != m_BorderHoverColor && m_BorderHoverColor.x != -1 && m_BorderHoverColor.y != -1 && m_BorderHoverColor.z != -1 && m_BorderHoverColor.w != -1) {
                m_CurrentBorderColor = m_BorderHoverColor;
                onInput = true;
                Fusion::UpdateWindow(GetCurrentWindow());
            }
            if (m_CurrentTextColor != m_TextHoverColor && m_TextHoverColor.x != -1 && m_TextHoverColor.y != -1 && m_TextHoverColor.z != -1 && m_TextHoverColor.w != -1) {
                m_CurrentTextColor = m_TextHoverColor;
                onInput = true;
                Fusion::UpdateWindow(GetCurrentWindow());
            }
            if(m_Clicked){
                m_Clicked = false;
            }
        }
        if(m_HoverCallback != nullptr){
            m_HoverCallback();
        }
    } else {
        if (io->Mouse[FUSION_MOUSE_BUTTON_1]) {
            if(!m_Clicked){
                m_Clicked = true;
            }
        }
        if (m_CurrentColor != m_BaseColor) {
            m_CurrentColor = m_BaseColor;
            onInput = true;
            Fusion::UpdateWindow(GetCurrentWindow());
        }
        if (m_CurrentBorderColor != m_BorderBaseColor) {
            m_CurrentBorderColor = m_BorderBaseColor;
            onInput = true;
            Fusion::UpdateWindow(GetCurrentWindow());
        }
        if (m_CurrentTextColor != m_TextBaseColor) {
            m_CurrentTextColor = m_TextBaseColor;
            onInput = true;
            Fusion::UpdateWindow(GetCurrentWindow());
        }
    }
}
void Fusion::Button::Render(Renderer2D* renderer) {
    renderer->DrawQuad(m_Position, m_Size, m_CurrentColor, m_Corners, m_BorderThickness, m_CurrentBorderColor, m_Texture, true);
    renderer->DrawString(m_Text, m_Font, m_Position + m_TextOffset, m_Size, m_CurrentTextColor);
    if (m_Icon != nullptr) {
        renderer->DrawQuad(m_Position + Math::Vec2{m_Size.x / 2 - m_IconSize.x / 2, m_Size.y / 2 - m_IconSize.y / 2} + m_IconOffset, m_IconSize, {0, 0, 0, 1}, {0, 0, 0, 0}, 0, {0, 0, 0, 0}, m_Icon,false);
    }
}
void Fusion::Button::SetText(const char* text) {
    m_Text = text;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetFont(const Fusion::Font* font) {
    m_Font = font;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetTextOffset(const Math::Vec2& offset) {
    m_TextOffset = offset;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetTexture(Fusion::GL::TextureData* texture) {
    m_Texture = texture;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetIcon(Fusion::GL::TextureData* icon) {
    m_Icon = icon;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetIconSize(const Math::Vec2& size) {
    m_IconSize = size;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetIconOffset(const Math::Vec2& offset) {
    m_IconOffset = offset;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetCorners(const Math::Vec4& corners) {
    m_Corners = corners;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetBorderThickness(float thickness) {
    m_BorderThickness = thickness;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetPosition(const Math::Vec2& position) {
    m_Position = position;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetSize(const Math::Vec2& size) {
    m_Size = size;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetBaseColor(const Math::Vec4& color) {
    m_BaseColor = color;
    m_CurrentColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetHoverColor(const Math::Vec4& color) {
    m_HoverColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetClickColor(const Math::Vec4& color) {
    m_ClickColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetBorderBaseColor(const Math::Vec4& color) {
    m_BorderBaseColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetBorderHoverColor(const Math::Vec4& color) {
    m_BorderHoverColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetBorderClickColor(const Math::Vec4& color) {
    m_BorderClickColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetTextBaseColor(const Math::Vec4& color) {
    m_TextBaseColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetTextHoverColor(const Math::Vec4& color) {
    m_TextHoverColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetTextClickColor(const Math::Vec4& color) {
    m_TextClickColor = color;
    Fusion::UpdateWindow(m_Window);
}
void Fusion::Button::SetHoverCallback(void (*callback)()) {
    m_HoverCallback = callback;
}
void Fusion::Button::SetClickCallback(void (* callback)()) {
    m_ClickCallback = callback;
}
void Fusion::Button::SetPressCallback(void (*callback)()) {
    m_PressCallback = callback;
}
void Fusion::AddButton(const char* name, bool dynamic, const char* window, uint8_t componentList) {
    auto button = new Button();
    button->m_Window = window;
    button->m_Name = name;
    Fusion::AddComponent(button, name, dynamic, window, componentList);
}
Fusion::Button* Fusion::GetButton(const char *name, const char *window) {
    return (Button*)GetComponent(name,window);
}

