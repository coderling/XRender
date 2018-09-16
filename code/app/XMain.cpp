#include <iostream>
#include "code/app/XApp.h"
#include "code/core/basic/Util.h"
#include "code/core/primitive/XPoint.h"
#include "code/core/primitive/PrimitiveUtil.h"
#include "code/core/math/Vector3.h"
#include "code/core/primitive/Vertex.h"
#include "code/core/primitive/Triangle.h"

void DrawTest()
{
    SDL_Surface* surface = pAppInstance->GetRenderSurface();
    SetWireDrawColor(surface->format, 45, 227, 215, 255);
    Uint32* pPixels = (Uint32*)surface->pixels;
    for(int row = 0; row < surface->h; ++row)
    {
        for(int col = 0; col < surface->w; ++col)
        {
            Uint32 ind = row * surface->w + col;
            pPixels[ind] = m_wireframeDC;
        }
    }
}

void TestUpdate()
{
    SDL_Surface* surface = pAppInstance->GetRenderSurface();
    XPoint points[40 * 80];
    for(int row = 0; row < 40; ++row)
    {
        for(int col = 0; col < 80; ++col)
        {
            points[row * 80 + col].x = row;
            points[row * 80 + col].y = col;
        }
    }
    SetWireDrawColor(surface->format, 0, 255, 0, 255);
    DrawPoints(surface, points, 40 * 80);
    SetWireDrawColor(surface->format, 0, 0, 255, 255);
    DrawLineDDA(surface, {0, 0}, {1280, 640});
    SetWireDrawColor(surface->format, 232, 30, 91, 255);
    //dy = 0
    DrawLineBresenham(surface, {0, 250}, {1280, 250});
    //dx = 0
    SetWireDrawColor(surface->format, 242, 159, 184, 255);
    DrawLineBresenham(surface, {500, 0}, {500, 640});
    //dy == dx
    SetWireDrawColor(surface->format, 169, 22, 222, 255);
    DrawLineBresenham(surface, {0, 0}, {600, 600});
    DrawLineBresenham(surface, {0, 600}, {600, 0});
    
    //dy != dx
    SetWireDrawColor(surface->format, 222, 32, 22, 255);
    DrawLineBresenham(surface, {40, 900}, {800, 50});
    DrawLineBresenham(surface, {50, 50}, {1000, 600});
}
    
    
    Triangle tri1;
    Color col(0, 0, 0, 0);
    Vector3 p1 = Vector3(0, 0, 0);
    Vector3 p2 = Vector3(0, 1, 0);
    Vector3 p3 = Vector3(1, 0, 0);
    
void TestTriangle()
{
    SDL_Surface* surface = pAppInstance->GetRenderSurface();
    SetWireDrawColor(surface->format, 0, 255, 0, 255);
    tri1.vertexics[0] = Vertex(p1, col);
    tri1.vertexics[1] = Vertex(p2, col);
    tri1.vertexics[2] = Vertex(p3, col);
    pAppInstance->PushVerteices(tri1.vertexics, 3, tri1.indexes, 3);

}

int main(int, char **)
{
    XApp::CreateAppSingleton("XApp_Alpha_0.1", 1280, 640, SDL_INIT_EVERYTHING, SDL_WINDOW_SHOWN
                    , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(pAppInstance != nullptr)
    {
        pAppInstance->SetCameraLookAt(Vector3(0, 0, -1), Vector3(0, 1, 0), Vector3(0, 0, 1));
        pAppInstance->AddUpdateLogic(TestUpdate);
        pAppInstance->AppLoop();
    }
    return 0;
}