#pragma once
#include "../Core/Core.h"
#include <vector>
#include <string>
namespace Fusion{
    struct IO{
        bool OnWindowMove = false;
        int WindowX = 100, WindowY = 100;
        bool OnWindowResize = false;
        int WindowWidth = 720, WindowHeight = 480;
        bool OnWindowFocus = false;
        bool OnWindowFocusLost = false;
        bool OnMouseMove = false;
        double MouseX = 0, MouseY = 0;
        bool OnMouseScroll = false;
        double MouseScrollX = 0;
        double MouseScrollY = 0;
        bool OnCharInput = false;
        char CharInput = '\0';
        bool OnFilesDrop = false;
        int DropFilesCount = 0;
        std::vector<std::string> DropFiles;
        bool Keyboard[348] = {false};
        bool Mouse[8] = {false};
        bool Joystick[16] = {false};
    };
}