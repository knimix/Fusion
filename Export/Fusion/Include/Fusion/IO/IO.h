#pragma once
#include "../Core/Core.h"
#include <vector>
#include <string>

#define Fusion_KEY_SPACE              32
#define Fusion_KEY_APOSTROPHE         39
#define Fusion_KEY_COMMA              44
#define Fusion_KEY_MINUS              45
#define Fusion_KEY_PERIOD             46
#define Fusion_KEY_SLASH              47
#define Fusion_KEY_0                  48
#define Fusion_KEY_1                  49
#define Fusion_KEY_2                  50
#define Fusion_KEY_3                  51
#define Fusion_KEY_4                  52
#define Fusion_KEY_5                  53
#define Fusion_KEY_6                  54
#define Fusion_KEY_7                  55
#define Fusion_KEY_8                  56
#define Fusion_KEY_9                  57
#define Fusion_KEY_SEMICOLON          59
#define Fusion_KEY_EQUAL              61
#define Fusion_KEY_A                  65
#define Fusion_KEY_B                  66
#define Fusion_KEY_C                  67
#define Fusion_KEY_D                  68
#define Fusion_KEY_E                  69
#define Fusion_KEY_F                  70
#define Fusion_KEY_G                  71
#define Fusion_KEY_H                  72
#define Fusion_KEY_I                  73
#define Fusion_KEY_J                  74
#define Fusion_KEY_K                  75
#define Fusion_KEY_L                  76
#define Fusion_KEY_M                  77
#define Fusion_KEY_N                  78
#define Fusion_KEY_O                  79
#define Fusion_KEY_P                  80
#define Fusion_KEY_Q                  81
#define Fusion_KEY_R                  82
#define Fusion_KEY_S                  83
#define Fusion_KEY_T                  84
#define Fusion_KEY_U                  85
#define Fusion_KEY_V                  86
#define Fusion_KEY_W                  87
#define Fusion_KEY_X                  88
#define Fusion_KEY_Y                  89
#define Fusion_KEY_Z                  90
#define Fusion_KEY_LEFT_BRACKET       91
#define Fusion_KEY_BACKSLASH          92
#define Fusion_KEY_RIGHT_BRACKET      93
#define Fusion_KEY_GRAVE_ACCENT       96
#define Fusion_KEY_WORLD_1            161
#define Fusion_KEY_WORLD_2            162
#define Fusion_KEY_ESCAPE             256
#define Fusion_KEY_ENTER              257
#define Fusion_KEY_TAB                258
#define Fusion_KEY_BACKSPACE          259
#define Fusion_KEY_INSERT             260
#define Fusion_KEY_DELETE             261
#define Fusion_KEY_RIGHT              262
#define Fusion_KEY_LEFT               263
#define Fusion_KEY_DOWN               264
#define Fusion_KEY_UP                 265
#define Fusion_KEY_PAGE_UP            266
#define Fusion_KEY_PAGE_DOWN          267
#define Fusion_KEY_HOME               268
#define Fusion_KEY_END                269
#define Fusion_KEY_CAPS_LOCK          280
#define Fusion_KEY_SCROLL_LOCK        281
#define Fusion_KEY_NUM_LOCK           282
#define Fusion_KEY_PRINT_SCREEN       283
#define Fusion_KEY_PAUSE              284
#define Fusion_KEY_F1                 290
#define Fusion_KEY_F2                 291
#define Fusion_KEY_F3                 292
#define Fusion_KEY_F4                 293
#define Fusion_KEY_F5                 294
#define Fusion_KEY_F6                 295
#define Fusion_KEY_F7                 296
#define Fusion_KEY_F8                 297
#define Fusion_KEY_F9                 298
#define Fusion_KEY_F10                299
#define Fusion_KEY_F11                300
#define Fusion_KEY_F12                301
#define Fusion_KEY_F13                302
#define Fusion_KEY_F14                303
#define Fusion_KEY_F15                304
#define Fusion_KEY_F16                305
#define Fusion_KEY_F17                306
#define Fusion_KEY_F18                307
#define Fusion_KEY_F19                308
#define Fusion_KEY_F20                309
#define Fusion_KEY_F21                310
#define Fusion_KEY_F22                311
#define Fusion_KEY_F23                312
#define Fusion_KEY_F24                313
#define Fusion_KEY_F25                314
#define Fusion_KEY_KP_0               320
#define Fusion_KEY_KP_1               321
#define Fusion_KEY_KP_2               322
#define Fusion_KEY_KP_3               323
#define Fusion_KEY_KP_4               324
#define Fusion_KEY_KP_5               325
#define Fusion_KEY_KP_6               326
#define Fusion_KEY_KP_7               327
#define Fusion_KEY_KP_8               328
#define Fusion_KEY_KP_9               329
#define Fusion_KEY_KP_DECIMAL         330
#define Fusion_KEY_KP_DIVIDE          331
#define Fusion_KEY_KP_MULTIPLY        332
#define Fusion_KEY_KP_SUBTRACT        333
#define Fusion_KEY_KP_ADD             334
#define Fusion_KEY_KP_ENTER           335
#define Fusion_KEY_KP_EQUAL           336
#define Fusion_KEY_LEFT_SHIFT         340
#define Fusion_KEY_LEFT_CONTROL       341
#define Fusion_KEY_LEFT_ALT           342
#define Fusion_KEY_LEFT_SUPER         343
#define Fusion_KEY_RIGHT_SHIFT        344
#define Fusion_KEY_RIGHT_CONTROL      345
#define Fusion_KEY_RIGHT_ALT          346
#define Fusion_KEY_RIGHT_SUPER        347
#define Fusion_KEY_MENU               348

#define FUSION_MOUSE_BUTTON_1         0
#define FUSION_MOUSE_BUTTON_2         1
#define FUSION_MOUSE_BUTTON_3         2
#define FUSION_MOUSE_BUTTON_4         3
#define FUSION_MOUSE_BUTTON_5         4
#define FUSION_MOUSE_BUTTON_6         5
#define FUSION_MOUSE_BUTTON_7         6
#define FUSION_MOUSE_BUTTON_8         7
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