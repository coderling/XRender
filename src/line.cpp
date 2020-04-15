#include "tgaimage.h"
#include <stdlib.h>

// Bresenham's line
void bresenham(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    bool steep = false;
    if(std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if(x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float delta = std::(dy/float(dx));
    float total = 0;
    int y = y0;
    int yd = y1 > y0 ? 1 : -1;
    for(int x = x0; x <= x1; x++)
    {
        if(steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }

        // 这样迭代省了四舍五入
        total += delta;
        if(total > 0.5)
        {
            y += yd;
            total -= 1.0;
        }
    }
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    bresenham(x0, y0, x1, y1, image, color);
}