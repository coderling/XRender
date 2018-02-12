
#include <SDL.h>

#include "XPoint.h"
#include "../../app/XApp.h"


inline bool IsPointInScreen(const SDL_Surface* pSurface, const int& x, const int& y)
{
    if(x < 0 || x >= pSurface->w || y < 0 || y >= pSurface->h)
    {
        //不在屏幕内
        return false;
    }

    return true;
}


//对浮点坐标进行取样，返回一个最近的整数坐标
inline void samplingPoint(const XPoint& p, int *x, int *y)
{
    *x = (int)(p.x + 0.5f);
    *y = (int)(p.y + 0.5f);
}

//对浮点坐标进行取样，返回一个最近的整数坐标
inline void samplingPoint(const float sx, const float sy, int *x, int *y)
{
    *x = (int)(sx + 0.5f);
    *y = (int)(sy + 0.5f);
}

void DrawPoint(const SDL_Surface* pSurface, const int& x, const int& y);

void DrawPoint(const XPoint& p);

void DrawPoints(XPoint const *pArr, int size);

void DrawLineDDA(const XPoint& st, const XPoint& ed);

void DrawLineBresenham(const XPoint& st, const XPoint& ed);