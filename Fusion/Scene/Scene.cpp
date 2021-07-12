#include "Scene.h"

void Fusion::Scene::OnLoad() {
    m_Loaded = true;
}
void Fusion::Scene::OnUnload() {
    m_Loaded = false;
}
