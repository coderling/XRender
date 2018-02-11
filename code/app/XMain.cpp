#include "includes.h"
#include <iostream>

void DrawTest()
{
    SDL_Surface* surface = pAppInstance->GetRenderSurface();
   
    pAppInstance->SetDrawColor(255, 0, 0);
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