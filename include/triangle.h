#pragma once

#include "line.h"
#include "geometry.h"
#include "tgaimage.h"
#include <stdlib.h>

const TGAColor twhite = TGAColor(255, 255, 255, 255);
const TGAColor tred = TGAColor(255, 0, 0, 255);

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, const TGAColor &color)
{
    if(t0.y > t1.y) std::swap(t0, t1);
    if(t0.y > t2.y) std::swap(t0, t2);
    if(t1.y > t2.y) std::swap(t1, t2);

    // fill 
    // 三角形分割
    int total_height = t2.y - t0.y;
    int segment_height = (t1.y - t0.y) + 1;
    //下半部分
    for(int y = t0.y; y <= t1.y; y++)
    {
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t0.y) / segment_height;
        Vec2i L = t0 + (t2 - t0) * alpha;
        Vec2i R = t0 + (t1 - t0) * beta;
        if(L.x > R.x) std::swap(L, R);
        for(int x = L.x; x <= R.x; x++)
        {
            image.set(x, y, color);
        }
    }
    //上半部分
    segment_height = (t2.y - t1.y) + 1;
    for(int y = t1.y+1; y <= t2.y; y++)
    {
        // 三角形相似
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t1.y) / segment_height;
        Vec2i L = t0 + (t2 - t0) * alpha;
        Vec2i R = t1 + (t2 - t1) * beta;
        if(L.x > R.x) std::swap(L, R);
        for(int x = L.x; x <= R.x; x++)
        {
            image.set(x, y, color);
        }
    }
}