#pragma once
#include "../Core/Core.h"
#include "../Components/Component.h"
#include <map>
namespace Fusion{
    class FUSION_API ComponentList{
    public:
        ComponentList() = default;
        bool AddComponent(Component* component,const char* name,bool dynamic);
        Component* GetComponent(const char* name);
        void Update(const IO* io,bool& onInput);
        void Render(Renderer2D* renderer);
        void Reset(bool total);
    private:
        std::map<std::string, Component*> m_DynamicComponents;
        std::map<std::string, Component*> m_StaticComponents;
    };
}