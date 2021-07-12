#pragma once
#include "../Core/Core.h"
#include "../IO/IO.h"
#include "../Renderer/Renderer2D.h"
#define FUSION_COMPONENT_LIST_BACK 0
#define FUSION_COMPONENT_LIST_MAIN 1
#define FUSION_COMPONENT_LIST_FRONT 2
namespace Fusion{
    class FUSION_API Component {
    public:
        Component() = default;
        virtual ~Component() = 0;
        virtual void Update(const Fusion::IO* io, bool& onInput) = 0;
        virtual void Render(Renderer2D* renderer) = 0;
    private:
    };

}