#include "ComponentList.h"

bool Fusion::ComponentList::AddComponent(Fusion::Component* component, const char* name, bool dynamic) {
    if(m_DynamicComponents.count(name) || m_StaticComponents.count(name)){
       return false;
    }
    if(dynamic){
        m_DynamicComponents.emplace(std::pair<std::string,Component*>(name,component));
    }else{
        m_StaticComponents.emplace(std::pair<std::string,Component*>(name,component));
    }
    return true;
}
Fusion::Component* Fusion::ComponentList::GetComponent(const char* name) {
    if(m_DynamicComponents.count(name)){
        return m_DynamicComponents.at(name);
    }
    if(m_StaticComponents.count(name)){
        return m_StaticComponents.at(name);
    }
    return nullptr;
}
void Fusion::ComponentList::Update(const Fusion::IO* io, bool& onInput) {
    std::map<std::string, Component*>::iterator it;
    for (it = m_StaticComponents.begin(); it != m_StaticComponents.end(); it++) {
        it->second->Update(io,onInput);
        if(onInput){
            return;
        }
    }
    for (it = m_DynamicComponents.begin(); it != m_DynamicComponents.end(); it++) {
        it->second->Update(io,onInput);
        if(onInput){
            return;
        }
    }
}
void Fusion::ComponentList::Render(Renderer2D* renderer) {
    std::map<std::string, Component*>::iterator it;
    for (it = m_DynamicComponents.begin(); it != m_DynamicComponents.end(); it++) {
        it->second->Render(renderer);
    }
    for (it = m_StaticComponents.begin(); it != m_StaticComponents.end(); it++) {
        it->second->Render(renderer);
    }
}
void Fusion::ComponentList::Reset(bool total) {
    if(total){
        std::map<std::string, Component*>::iterator it;
        for (it = m_DynamicComponents.begin(); it != m_DynamicComponents.end(); it++) {
            delete it->second;
        }
        for (it = m_StaticComponents.begin(); it != m_StaticComponents.end(); it++) {
            delete it->second;
        }
        m_DynamicComponents.clear();
        m_StaticComponents.clear();
    }else{
        std::map<std::string, Component*>::iterator it;
        for (it = m_DynamicComponents.begin(); it != m_DynamicComponents.end(); it++) {
            delete it->second;
        }
        m_DynamicComponents.clear();
    }
}

