#include "tgaimage.h"
#include "geometry.h"
#include <stdlib.h>

// Bresenham's line
void bresenham(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color)
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

    int dx = x1 - x0;
    int dy = y1 - y0;
    int delta = std::abs(dy)*2;
    int total = 0;
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

        total += delta;
        if(total > dx)
        {
            y += yd;
            total -= dx * 2;
        }
    }
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color)
{
    bresenham(x0, y0, x1, y1, image, color);
}

void line(Vec2i t1, Vec2i t2, TGAImage &image, const TGAColor &color)
{
    line(t1.x, t1.y, t2.x, t2.y, image, color);
}