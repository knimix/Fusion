#include "WindowManager.h"
#include <map>
#include "../GL/GLCore.h"
#include "../Renderer/Renderer2D.h"
#include "../Lists/ComponentList.h"
#include "../Lists/TextureList.h"
#include "../Lists/FontList.h"
#include <chrono>
#include <thread>

struct Window {
    const char* Name = nullptr;
    GLFWwindow* NativeWindow = nullptr;
    Fusion::WindowDesign* design = nullptr;
    Fusion::IO* IO = nullptr;
    Fusion::Renderer2D* Renderer = nullptr;
    Fusion::ComponentList* BackComponentList = nullptr;
    Fusion::ComponentList* MainComponentList = nullptr;
    Fusion::ComponentList* FrontComponentList = nullptr;
    Fusion::TextureList* TextureList = nullptr;
    Fusion::FontList* FontList = nullptr;
    std::map<std::string, Fusion::Scene*> Scenes;
    Fusion::Scene* CurrentScene = nullptr;
    const char* Title = "Fusion GXF Library";
    bool Update = false;
};
struct FrameData {
    double FPS = 72;
    double StartTime = 0;
    double StopTime = 0;
    double FrameTime = 0;
    double DeltaTime = 0;
};
static std::map<std::string, Window*> s_Windows;
static Window* s_CurrentWindow;
static FrameData s_FrameData;
static Window* GetWindow(GLFWwindow* nativeWindow) {
    std::map<std::string, Window*>::iterator it;
    Window* window = nullptr;
    for (it = s_Windows.begin(); it != s_Windows.end(); it++) {
        window = it->second;
        if (window->NativeWindow == nativeWindow) {
            break;
        }
        window = nullptr;
    }
    return window;
}
void Fusion::CreateWindow(WindowDesign* design, const char* name) {
    if (!s_Windows.count(name)) {
        auto window = new Window;
       auto io = new Fusion::IO;
        window->Name = name;
        window->design = design;
        window->IO = io;
        window->BackComponentList = new ComponentList();
        window->MainComponentList = new ComponentList();
        window->FrontComponentList = new ComponentList();
        window->TextureList = new TextureList();
        window->FontList = new FontList();
        glfwWindowHint(GLFW_SAMPLES, 4);
        window->NativeWindow = glfwCreateWindow(io->WindowWidth, io->WindowHeight, window->Title, nullptr, nullptr);
        if (window->NativeWindow == nullptr) {
            return;
        }
        glfwSetWindowPos(window->NativeWindow, io->WindowX, io->WindowY);
        glfwMakeContextCurrent(window->NativeWindow);
        glfwSetWindowPosCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, int x, int y) {
            std::map<std::string, Window*>::iterator it;
            Window* window = nullptr;
            for (it = s_Windows.begin(); it != s_Windows.end(); it++) {
                window = it->second;
                if (window->NativeWindow == nativeWindow) {
                    break;
                }
                window = nullptr;
            }
            if (window != nullptr) {
                IO* io = window->IO;
                io->WindowX = x;
                io->WindowY = y;
                io->OnWindowMove = true;
            }
        });
        glfwSetWindowSizeCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, int width, int height) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->WindowWidth = width;
                io->WindowHeight = height;
                io->OnWindowResize = true;
            }
        });
        glfwSetWindowFocusCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, int focus) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                if (focus) {
                    io->OnWindowFocus = true;
                } else {
                    io->OnWindowFocusLost = true;
                }
            }
        });
        glfwSetCursorPosCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, double mouseX, double mouseY) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->OnMouseMove = true;
                io->MouseX = mouseX;
                io->MouseY = mouseY;
            }
        });
        glfwSetScrollCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, double xOffset, double yOffset) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->OnMouseScroll = true;
                io->MouseScrollX = xOffset;
                io->MouseScrollY = yOffset;
            }
        });
        glfwSetCharCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, unsigned int key) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->OnCharInput = true;
                io->CharInput = (char) key;
            }
        });
        glfwSetKeyCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, int key, int scanCode, int action, int mods) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->Keyboard[key] = action;
            }
        });
        glfwSetDropCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, int count, const char* files[]) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->OnFilesDrop = true;
                io->DropFilesCount = count;
                io->DropFiles.clear();
                for (int i = 0; i < count; i++) {
                    io->DropFiles.emplace_back(files[i]);
                }
            }
        });
        glfwSetMouseButtonCallback(window->NativeWindow, [](GLFWwindow* nativeWindow, int button, int action, int mods) {
            Window* window = GetWindow(nativeWindow);
            if (window != nullptr) {
                IO* io = window->IO;
                io->Mouse[button] = action;
            }
        });
        glfwSwapInterval(1);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            return;
        }
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, io->WindowWidth, io->WindowHeight);
        window->Update = true;

        auto renderer = new Fusion::Renderer2D(io);
        window->Renderer = renderer;

        s_Windows.emplace(std::pair<const char*, Window*>(name, window));
    }
}
void Fusion::DestroyWindow(const char* name) {
    if (s_Windows.count(name)) {
        Window* window = s_Windows.at(name);
        glfwDestroyWindow(window->NativeWindow);
        delete window->IO;
        delete window->Renderer;
        s_Windows.erase(name);
        delete window;
    }
}
void Fusion::SetWindowPosition(const char* name, const Math::Vec2& position) {
    if (s_Windows.count(name)) {
        Window* window = s_Windows.at(name);
        glfwSetWindowPos(window->NativeWindow, (int) position.x, (int) position.y);
    }
}
void Fusion::SetWindowSize(const char* name, const Math::Vec2& size) {
    if (s_Windows.count(name)) {
        Window* window = s_Windows.at(name);
        glfwSetWindowSize(window->NativeWindow, (int) size.x, (int) size.y);
    }
}
void Fusion::UpdateWindow(const char *name) {
    if (!s_Windows.count(name)) {
        return;
    }
    Window* window = s_Windows.at(name);
    window->Update = true;
}
const char* Fusion::GetCurrentWindow() {
    return s_CurrentWindow->Name;
}
Fusion::IO* Fusion::GetIO(const char* name) {
    if (s_Windows.count(name)) {
        return s_Windows.at(name)->IO;
    }
    return nullptr;
}
void Fusion::AddComponent(Component* component, const char* name, bool dynamic, const char* window, uint8_t componentList) {
    if (component == nullptr) {
        return;
    }
    if (!s_Windows.count(window)) {
        return;
    }
    Window* targetWindow = s_Windows.at(window);
    bool result = false;
    switch (componentList) {
        case FUSION_COMPONENT_LIST_BACK:
            result = targetWindow->BackComponentList->AddComponent(component, name, dynamic);
            break;
        case FUSION_COMPONENT_LIST_MAIN:
            result = targetWindow->MainComponentList->AddComponent(component, name, dynamic);
            break;
        case FUSION_COMPONENT_LIST_FRONT:
            result = targetWindow->FrontComponentList->AddComponent(component, name, dynamic);
            break;
        default:
            result = targetWindow->MainComponentList->AddComponent(component, name, dynamic);
            break;
    }
    if(!result){
        delete component;
    }
}
Fusion::Component* Fusion::GetComponent(const char* name, const char* window) {
    Window* targetWindow = s_Windows.at(window);
    if (targetWindow == nullptr) {
        return nullptr;
    }
    Component* component = targetWindow->BackComponentList->GetComponent(name);
    if(component != nullptr){
        return component;
    }
    component = targetWindow->MainComponentList->GetComponent(name);
    if(component != nullptr){
        return component;
    }
    component = targetWindow->FrontComponentList->GetComponent(name);
    if(component != nullptr){
        return component;
    }
    return nullptr;
}
void Fusion::AddTexture(const char* path, const char* name, const char* window, bool dynamic) {
    if(!s_Windows.count(window)){
        return;
    }
    Window* targetWindow = s_Windows.at(window);
    if(targetWindow == nullptr){
        return;
    }
    glfwMakeContextCurrent(targetWindow->NativeWindow);
    targetWindow->TextureList->AddTexture(path,name,dynamic);
}
Fusion::GL::TextureData* Fusion::GetTexture(const char* name, const char* window) {
    if(!s_Windows.count(window)){
        return nullptr;
    }
    Window* targetWindow = s_Windows.at(window);
    if (targetWindow == nullptr) {
        return nullptr;
    }
    return targetWindow->TextureList->GetTexture(name);
}
void Fusion::AddFont(const char *path, int fontSize, const char *name, const char *window, bool dynamic) {
    if(!s_Windows.count(window)){
        return;
    }
    Window* targetWindow = s_Windows.at(window);
    if(targetWindow == nullptr){
        return;
    }
    glfwMakeContextCurrent(targetWindow->NativeWindow);
    Font* font = new Font(path,fontSize);
    if(font->m_IsCreated){
        targetWindow->FontList->AddFont(font,name,dynamic);
    }
}
const Fusion::Font* Fusion::GetFont(const char *name, const char *window) {
    if(!s_Windows.count(window)){
        return nullptr;
    }
    Window* targetWindow = s_Windows.at(window);
    if (targetWindow == nullptr) {
        return nullptr;
    }
    return targetWindow->FontList->GetFont(name);
}
void Fusion::AddScene(const char *name, Scene *scene, const char *window) {
    if(!s_Windows.count(window)){
        return;
    }
    Window* targetWindow = s_Windows.at(window);
    if(targetWindow->Scenes.count(name)){
        return;
    }
    scene->m_Name = name;
    targetWindow->Scenes.insert(std::pair<std::string, Scene*>(name,scene));
}
void Fusion::LoadScene(const char *scene, const char *window) {
    if(!s_Windows.count(window)){
        return;
    }
    Window* targetWindow = s_Windows.at(window);
    if(!targetWindow->Scenes.count(scene)){
        return;
    }
    if(targetWindow->CurrentScene != nullptr){
        targetWindow->CurrentScene->OnUnload();
        targetWindow->FrontComponentList->Reset(false);
        targetWindow->MainComponentList->Reset(false);
        targetWindow->BackComponentList->Reset(false);
        targetWindow->TextureList->Reset(false);
        targetWindow->FontList->Reset(false);
    }
    Scene* targetScene = targetWindow->Scenes.at(scene);
    if(!targetScene->m_Loaded){
        glfwMakeContextCurrent(targetWindow->NativeWindow);
        targetWindow->CurrentScene = targetScene;
        targetScene->OnLoad();
    }

}
void Fusion::UnloadScene(const char *scene, const char *window) {
    if(!s_Windows.count(window)){
        return;
    }
    Window* targetWindow = s_Windows.at(window);
    if(!targetWindow->Scenes.count(scene)){
        return;
    }
    Scene* targetScene = targetWindow->Scenes.at(scene);
    if(targetScene->m_Loaded){
        glfwMakeContextCurrent(targetWindow->NativeWindow);
        targetScene->OnUnload();
        targetWindow->CurrentScene->OnUnload();
        targetWindow->FrontComponentList->Reset(false);
        targetWindow->MainComponentList->Reset(false);
        targetWindow->BackComponentList->Reset(false);
        targetWindow->TextureList->Reset(false);
        targetWindow->FontList->Reset(false);
        targetWindow->Update = true;
    }

}
Fusion::Scene* Fusion::GetCurrentScene(const char *window) {
    if(!s_Windows.count(window)){
        return nullptr;
    }
    Window* targetWindow = s_Windows.at(window);
    return targetWindow->CurrentScene;
}
void Fusion::Begin() {
    s_FrameData.StartTime = glfwGetTime();
}
void Fusion::Update() {
    glfwPollEvents();
    std::map<std::string, Window*>::iterator it;
    for (it = s_Windows.begin(); it != s_Windows.end(); it++) {
        Window* window = it->second;
        s_CurrentWindow = window;
        if (glfwWindowShouldClose(window->NativeWindow)) {
            DestroyWindow(it->first.c_str());
            break;
        }
        if (window->IO->OnWindowResize) {
            glfwMakeContextCurrent(s_CurrentWindow->NativeWindow);
            glViewport(0, 0, window->IO->WindowWidth, window->IO->WindowHeight);
            window->Update = true;
        }
        bool onInput = false;
        window->FrontComponentList->Update(window->IO, onInput);
        if (onInput) {
            continue;
        }
        window->MainComponentList->Update(window->IO, onInput);
        if (onInput) {
            continue;
        }
        window->BackComponentList->Update(window->IO, onInput);
        if (onInput) {
            continue;
        }
    }
}
void Fusion::Render() {
    std::map<std::string, Window*>::iterator it;
    for (it = s_Windows.begin(); it != s_Windows.end(); it++) {
        Window* window = it->second;
        s_CurrentWindow = window;
        if (window->Update) {
            window->Update = false;
            glfwMakeContextCurrent(window->NativeWindow);
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.1, 0.1, 0.1, 1.0);
            window->Renderer->BeginBatch();
            //rendering

            window->BackComponentList->Render(window->Renderer);
            window->MainComponentList->Render(window->Renderer);
            window->FrontComponentList->Render(window->Renderer);

            window->Renderer->EndBatch();
            window->Renderer->Flush();
            glfwSwapBuffers(window->NativeWindow);
        }
    }
}
void Fusion::End() {
    std::map<std::string, Window*>::iterator it;
    for (it = s_Windows.begin(); it != s_Windows.end(); it++) {
        IO* io = it->second->IO;
        io->OnWindowMove = false;
        io->OnWindowResize = false;
        io->OnMouseMove = false;
        io->OnCharInput = false;
        io->OnFilesDrop = false;
        io->OnWindowFocus = false;
        io->OnWindowFocusLost = false;
        io->OnMouseScroll = false;
    }
    s_FrameData.StopTime = glfwGetTime();
    s_FrameData.FrameTime = s_FrameData.StopTime - s_FrameData.StartTime;
    s_FrameData.DeltaTime = s_FrameData.FrameTime * 100;
    double sleepTime = (1.0 / s_FrameData.FPS) - s_FrameData.FrameTime;
    if (sleepTime > 0.0) {
        std::this_thread::sleep_for(std::chrono::milliseconds((long) (sleepTime * 1000)));
    }
}