#include <iostream>
#include "Fusion/WindowManager/WindowManager.h"
#include <GLFW/glfw3.h>

#include <thread>

#include "Fusion/Components/Components.h"


class TestScene : public Fusion::Scene{
    void OnLoad() override;
};
void TestScene::OnLoad() {
    Scene::OnLoad();
  //  Fusion::AddTexture("check.png","icon","window2",true);
  //  Fusion::AddTexture("test.jpg","back","window2",true);


    Fusion::AddFont("Cousine-Regular.ttf",13,"font","window2",true);
    Fusion::AddFont("Cousine-Regular.ttf",27,"fon2","window2",true);

    Fusion::AddButton("home",true,"window2");
    Fusion::AddButton("start",true,"window2");
    Fusion::AddButton("start2",true,"window2");
    auto homeButton = Fusion::GetButton("home","window2");

    homeButton->SetBaseColor({0.2,0.3,0.4,1.0});
    homeButton->SetPosition({200,300});
    homeButton->SetFont(Fusion::GetFont("font","window2"));
    homeButton->SetText("Home");
    homeButton->SetBorderThickness(3);
    homeButton->SetBorderBaseColor({1.0,1.0,1.0,1.0});
    homeButton->SetHoverColor({0.3,0.4,0.5,1.0});
    homeButton->SetCorners({10,10,10,10});
    homeButton->SetTextClickColor({0.2,0.3,0.4,1.0});
    homeButton->SetTextHoverColor({1.0,1.0,1.0,1.0});
    homeButton->SetBorderHoverColor({1.0,1.0,1.0,1.0});
    homeButton->SetBorderClickColor({0.8,0.3,0.4,1.0});

    homeButton->SetClickCallback([](){
       std::cout << "hover\n";
    });

    homeButton->SetClickColor({1.0,1.0,1.0,1.0});


    auto startButton = Fusion::GetButton("start","window2");

    startButton->SetBaseColor({0.8,0.3,0.3,1.0});
    startButton->SetPosition({100,200});
    startButton->SetSize({200,80});
    startButton->SetFont(Fusion::GetFont("fon2","window2"));
    startButton->SetText("Home");
    startButton->SetBorderThickness(0);
    startButton->SetBorderBaseColor({1.0,1.0,1.0,1.0});
    startButton->SetHoverColor({0.9,0.4,0.4,1.0});
    startButton->SetCorners({20,20,20,20});


    auto startButton2 = Fusion::GetButton("start2","window2");

    startButton2->SetBaseColor({0.0,0.0,0.0,0.0});
    startButton2->SetPosition({350,200});
    startButton2->SetSize({100,40});
    startButton2->SetFont(Fusion::GetFont("font","window2"));
    startButton2->SetText("Home");
    startButton2->SetBorderThickness(3);
    startButton2->SetBorderBaseColor({1.0,1.0,1.0,1.0});
    startButton2->SetHoverColor({0.1,0.1,0.1,1.0});
    startButton2->SetCorners({10,10,10,10});
    startButton2->SetTextClickColor({0.2,0.3,0.4,1.0});
    startButton2->SetTextHoverColor({1.0,1.0,1.0,1.0});
    startButton2->SetBorderHoverColor({1.0,1.0,1.0,1.0});
    startButton2->SetBorderClickColor({0.8,0.3,0.4,1.0});
}

class TestScene2 : public Fusion::Scene{
    void OnLoad() override ;
};
void TestScene2::OnLoad() {
    Scene::OnLoad();
    Fusion::AddTexture("check.png","icon","window2",true);
    Fusion::AddTexture("test.jpg","back","window2",true);

  Fusion::AddButton("test2",true,"window2");
   Fusion::AddButton("test2",true,"window2");


}
int main() {



    std::cout << glfwInit() << std::endl;
    Fusion::WindowDesign* design = new Fusion::WindowDesign;

    Fusion::CreateWindow(design, "window2");
    //Fusion::CreateWindow(design, "window3");

    TestScene* scene = new TestScene();
    TestScene2* scene2 = new TestScene2();

    Fusion::AddScene("test",scene,"window2");
    Fusion::AddScene("test2",scene2,"window2");



    bool activate = false;
    bool running = true;

    Fusion::LoadScene("test","window2");

    while (true) {
        Fusion::Begin();

        Fusion::Update();


        Fusion::Render();

        Fusion::End();
    }
}
