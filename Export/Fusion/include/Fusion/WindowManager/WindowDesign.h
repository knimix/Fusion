#pragma once
#include "Fusion/Core/Core.h"
#include "Math/Vector/Vec4/Vec4.h"
namespace Fusion{
    struct FUSION_API WindowDesign{
        Math::Vec4 BackgroundColor;
        void (*OnLoad)();
        void (*OnUnload)();
        void (*OnRender)();
        void (*OnUpdate)();
    };
}