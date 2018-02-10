#include<SDL.h>
#include<iostream>


int main(int, char **)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout <<"SDL_Init: " <<SDL_GetError() <<std::endl;
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("helloSDL", 100, 100, 800, 600,
                                            SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        std::cout <<"SDL_CreateWindow: " <<SDL_GetError() <<std::endl;
        return 1;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1,
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(nullptr == render)
    {
        std::cout <<"SDL_CreateRenderer: " <<SDL_GetError() <<std::endl;
        return 1;
    }

    SDL_SetRenderDrawColor(render, 45, 167, 227, 255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);
    SDL_Delay(5000);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
