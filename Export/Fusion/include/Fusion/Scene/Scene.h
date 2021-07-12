#pragma once
#include "../Core/Core.h"
namespace Fusion{
    class FUSION_API Scene {
    public:
        Scene() = default;
        virtual void OnLoad();
        virtual void OnUnload();
        bool m_Loaded = false;
        const char* m_Name = nullptr;
    private:
    };

}