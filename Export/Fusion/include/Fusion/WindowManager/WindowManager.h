#pragma once
#include "../WindowManager/WindowDesign.h"
#include "../IO/IO.h"
#include <Math/Vector/Vec2/Vec2.h>
#include "../Components/Component.h"
#include "../Font/Font.h"
namespace Fusion{
    void FUSION_API CreateWindow(WindowDesign* design, const char* name);
    void FUSION_API DestroyWindow(const char* name);
    void FUSION_API SetWindowPosition(const char* name, const Math::Vec2& position);
    void FUSION_API SetWindowSize(const char* name, const Math::Vec2& size);
    void FUSION_API UpdateWindow(const char* name);
    const char* GetCurrentWindow();
    IO* GetIO(const char* name);
    void AddComponent(Component* component,const char* name, bool dynamic, const char* window, uint8_t componentList = FUSION_COMPONENT_LIST_MAIN);
    Component* GetComponent(const char* name, const char* window);
    void AddTexture(const char* path,const char* name, const char* window, bool dynamic);
    GL::TextureData* GetTexture(const char* name, const char* window);
    void AddFont(const char* path, int fontSize, const char* name, const char* window, bool dynamic);
    Fusion::Font* GetFont(const char* name, const char* window);


    void FUSION_API Begin();
    void FUSION_API Update();
    void FUSION_API Render();
    void FUSION_API End();
}
