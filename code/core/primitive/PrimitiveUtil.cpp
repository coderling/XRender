#include "PrimitiveUtil.h"
#include <iostream>
#include <math.h>

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

inline void DrawPoint(const SDL_Surface* pSurface, const int& x, const int& y)
{
    if(!IsPointInScreen(pSurface, x, y))
    {
        //不在屏幕内
        return;
    }
    Uint32 dc = pAppInstance->GetDrawColor();
    int drawInd = y * pSurface->w + x;
    Uint32* pPixels = (Uint32*)pSurface->pixels;
    //std::cout <<"DrawPoint: " <<drawInd <<std::endl;
    pPixels[drawInd] = dc;
}

void DrawPoint(const XPoint& p)
{
    SDL_Surface* pSurface = pAppInstance->GetRenderSurface();

    int x, y;
    samplingPoint(p, &x, &y);
    DrawPoint(pSurface, x, y);
}

void DrawPoints(XPoint const *pArr, int size)
{
    SDL_Surface* pSurface = pAppInstance->GetRenderSurface();
    
    
    for(int ind = 0; ind < size; ++ind)
    {
        int x, y;
        samplingPoint(pArr[ind], &x, &y);
        DrawPoint(pSurface, x, y);
    }
}

//DDA(数字微波分析仪)划线算法
void DrawLineDDA(const XPoint& st, const XPoint& ed)
{
    float dx = ed.x - st.x;
    float dy = ed.y - st.y;

    float xInc, yInc, x = st.x, y = st.y, steps;

    if(fabs(dx) > fabs(dy))
    {
        //x方向便宜量大于y，步长取x方向绝对值=1，计算y方向步长
        steps = dx;
    }
    else
    {
        steps = dy;
    }

    xInc = dx / steps;
    yInc = dy / steps;
    SDL_Surface* pSurface = pAppInstance->GetRenderSurface();
    int samX, samY;
    for(int k = 0; k < steps; ++k)
    {
        x += xInc;
        y += yInc;
        samplingPoint(x, y, &samX, &samY);
        //std::cout <<"DrawLineDDA: " <<samX<< " " <<samY <<std::endl;
        DrawPoint(pSurface, samX, samY);
    }
}

//对于直线y = mx + b分为四种情况, dx, dy 表示偏移量
//1. 斜率 0 < m < 1, 决策参数p0 = 2dy - dx pk+1 = pk + 2dy - 2dx 或者 pk+1 = pk + 2dy，这取决于pk的符号
//2. 斜率 m > 1，思路上相对于1，交换x, y的位置，采用一样的迭代规则
//3. 斜率 -1 < m < 0, 决策参数p0 = 2dy + dx, pk+1 = pk + 2dy + 2dx 或者 pk+1 = pk + 2dy 这取决于pk的符号
//4. 斜率 m < -1, 同理，相对于3，交换x, y的位置，采用一样的迭代规则
//最后对比1，3的pk的计算，如果我们dx, dy 取绝对值，这两种情况可以合并成2一种.
//ps: 边界处理,对于dx = 0 dy = 0, fabs(dx) = fabs(dy), 可以直接处理，不需要执行画线算法
//最后的最后，这里定义的点结构提是float类型的坐标，需要先对端点坐标取整，这里接单调用samplingPoint()来取较近的整数点
void DrawLineBresenham(const XPoint& st, const XPoint& ed)
{
    int sx, sy, ex, ey;
    int dx, dy, p, towDy, twoDyMinusDx;

    samplingPoint(st, &sx, &sy);
    samplingPoint(ed, &ex, &ey);

    dx = abs(ex - sx), dy = abs(ey - sy);

    twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx)
    p = twoDy - dx;

    int x, y;
    //
    if(sx > ex)
    {

    }
}