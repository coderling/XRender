#include "PrimitiveUtil.h"
#include <iostream>
#include <math.h>


void DrawPoint(const SDL_Surface* pSurface, const int& x, const int& y)
{
    if(!IsPointInScreen(pSurface, x, y))
    {
        //不在屏幕内
        return;
    }
    Uint32 dc = m_wireframeDC;
    int drawInd = y * pSurface->w + x;
    Uint32* pPixels = (Uint32*)pSurface->pixels;
    //std::cout <<"DrawPoint: " <<drawInd <<std::endl;
    pPixels[drawInd] = dc;
}

void DrawPoint(const SDL_Surface* pSurface, const XPoint& p)
{
    int x, y;
    samplingPoint(p, &x, &y);
    DrawPoint(pSurface, x, y);
}

void DrawPoints(const SDL_Surface* pSurface, XPoint const *pArr, int size)
{
    for(int ind = 0; ind < size; ++ind)
    {
        int x, y;
        samplingPoint(pArr[ind], &x, &y);
        DrawPoint(pSurface, x, y);
    }
}
