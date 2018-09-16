#include "PrimitiveUtil.h"
#include <iostream>
#include <math.h>


//DDA(数字微波分析仪)划线算法
void DrawLineDDA(const SDL_Surface* pSurface, const XPoint& st, const XPoint& ed)
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
    int samX, samY;
    samplingPoint(x, y, &samX, &samY);
    DrawPoint(pSurface, samX, samY);
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

inline void swap(int& a, int& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

//分开两个函数主要想要减少是否切换了XY轴的判断，只需要判断一次
void DrawLineBresenhamXY(const SDL_Surface* pSurface, const int& dx, const int&dy,
                         int& x, int& y,
                         const int& step, const int& ex)
{
     /*上面交换之后dx肯定比dy大
    if(dx == 0)
    {
        for(int k = 0; k <= dy; ++k)
        {
            DrawPoint(pSurface, x, y++);
        }
        return;
    }
    */
    int p, twoDy, twoDyMinusDx;
    if(dy == 0)
    {
        for(int k = 0; k <= dx; ++k)
        {
            DrawPoint(pSurface, x++, y);
        }
        return;
    }
    

    if(dx == dy)
    {
        for(int k = 0; k <= dy; ++k)
        {
            DrawPoint(pSurface, x++, y);
            y += step;
        }
        return;
    }
 

    twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    p = twoDy - dx;
    
    DrawPoint(pSurface, x, y);
    while(x < ex)
    {
        ++x;
        if(p < 0)
        {
            p += twoDy;
        }
        else
        {
            y += step;
            p += twoDyMinusDx;
        }
        DrawPoint(pSurface, x, y);
    }
}

void DrawLineBresenhamYX(const SDL_Surface* pSurface, const int& dx, const int&dy,
                         int& x, int& y,
                         const int& step, const int& ex)
{
    int p, twoDy, twoDyMinusDx;

    if(dy == 0)
    {
        for(int k = 0; k <= dx; ++k)
        {
            DrawPoint(pSurface, y, x++);
        }
        return;
    }
    

    if(dx == dy)
    {
        for(int k = 0; k <= dy; ++k)
        {
            DrawPoint(pSurface, y, x++);
            y += step;
        }
        return;
    }
 

    twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    p = twoDy - dx;
    
    DrawPoint(pSurface, y, x);
    while(x < ex)
    {
        ++x;
        if(p < 0)
        {
            p += twoDy;
        }
        else
        {
            y += step;
            p += twoDyMinusDx;
        }
        DrawPoint(pSurface, y, x);
    }
}

void DrawLineBresenham(const SDL_Surface* pSurface, const XPoint& st, const XPoint& ed)
{
    int sx, sy, ex, ey;
    int dx, dy;

    samplingPoint(st, &sx, &sy);
    samplingPoint(ed, &ex, &ey);

    dx = abs(ex - sx), dy = abs(ey - sy);
    

    int x, y;
    bool bSwitch = false; //是否交换了x,y;
   
    //斜率绝对值大于1，交换x,y
    if(dy > dx)
    {
        swap(dy, dx);
        swap(sy, sx);
        swap(ey, ex);
        bSwitch = true;
    }


    //需要根据斜率的正负来判定y方向的迭代是+1还是-1
    int step = (ex - sx) * (ey - sy) < 0 ? -1 : 1;

    //为了保证相同的两个端点，画出来的线是一致的，并递增迭代，从x比较小的端点开始迭代
    if(sx > ex)
    {
        x = ex;
        y = ey;
        ex = sx;
    }
    else
    {
        x = sx;
        y = sy;
    }

    if(bSwitch)
    {
        DrawLineBresenhamYX(pSurface, dx, dy, x, y, step, ex);
    }
    else
    {
        DrawLineBresenhamXY(pSurface, dx, dy, x, y, step, ex);
    }
}