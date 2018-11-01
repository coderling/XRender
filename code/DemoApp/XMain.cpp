#include <iostream>
#include "code/app/XApp.h"
#include "code/core/basic/Util.h"
#include "TestScene.h"

int main(int, char **)
{
    XApp::CreateAppSingleton("XApp_Alpha_0.1", 1280, 640, SDL_INIT_EVERYTHING, SDL_WINDOW_SHOWN
                    , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(pAppInstance != nullptr)
    {
        pAppInstance->SetCameraLookAt(Vector3(0, 0, -5), Vector3(0, 1, 0), Vector3(0, 0, 1));
        TestScene ts;
        ts.Start();
        pAppInstance->AppLoop();
    }
    return 0;
}