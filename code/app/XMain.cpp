#include "XApp.h"

void DrawTest()
{
    SDL_Surface* surface = pAppInstance->GetRenderSurface();
    if(SDL_MUSTLOCK(surface))
    {
        SDL_LockSurface(surface);
    } 
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
    if(SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

void TestUpdate()
{
     DrawTest();
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