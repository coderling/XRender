#include "../includes.h"
#include <iostream>

void DrawTest()
{
    SDL_Surface* surface = pAppInstance->GetRenderSurface();
   
    pAppInstance->SetDrawColor(45, 227, 215);
    Uint32 dc = pAppInstance->GetDrawColor();
    Uint32* pPixels = (Uint32*)surface->pixels;
    for(int row = 0; row < surface->h; ++row)
    {
        for(int col = 0; col < surface->w; ++col)
        {
            Uint32 ind = row * surface->w + col;
            pPixels[ind] = dc;
        }
    }
}

void TestUpdate()
{
    DrawTest();
    XPoint points[40 * 80];
    for(int row = 0; row < 40; ++row)
    {
        for(int col = 0; col < 80; ++col)
        {
            points[row * 80 + col].x = row;
            points[row * 80 + col].y = col;
        }
    }
    pAppInstance->SetDrawColor(0, 255, 0);
    DrawPoints(points, 40 * 80);
    pAppInstance->SetDrawColor(0, 0, 255);
    DrawLineDDA({0, 0}, {1280, 640});
    pAppInstance->SetDrawColor(232, 30, 91);
    //dy = 0
    DrawLineBresenham({0, 250}, {1280, 250});
    //dx = 0
    pAppInstance->SetDrawColor(242, 159, 184);
    DrawLineBresenham({500, 0}, {500, 640});
    //dy == dx
    pAppInstance->SetDrawColor(169, 22, 222);
    DrawLineBresenham({0, 0}, {600, 600});
    DrawLineBresenham({0, 600}, {600, 0});
    
    //dy != dx
    pAppInstance->SetDrawColor(222, 32, 22);
    DrawLineBresenham({40, 900}, {800, 50});
    DrawLineBresenham({50, 50}, {1000, 600});
}

int main(int, char **)
{

    XApp app = XApp("XApp_Alpha_0.1", 1280, 640, SDL_INIT_EVERYTHING, SDL_WINDOW_SHOWN
                    , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    pAppInstance = &app;
    
    pAppInstance->AddUpdateLogic(TestUpdate);
    pAppInstance->AppLoop();
    return 0;
}