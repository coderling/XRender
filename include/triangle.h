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

// 求重心坐标
Vec3f barycentric(Vec2i *points, Vec2i p)
{
    Vec3f v1(points[2][0] - points[0][0], points[1][0] - points[0][0], points[0][0] - p[0]);
    Vec3f v2(points[2][1] - points[0][1], points[1][1] - points[0][1], points[0][1] - p[0]);
    Vec3f u = cross(v1, v2);
    // y < 0 说明，v1,v2，向量共线, 随便返回< 0 vec3
    if(std::abs(u[2]) < 1) return Vec3f(-1, 1, 1);
    return Vec3f(1.0f - (u.x + u.y)/u.z, u.y/u.z, u.x/ u.z);
}

void triangleBoundingbox(Vec2i *points, TGAImage &image, TGAColor color)
{
    int width = image.get_width();
    int height = image.get_height();
    Vec2i bboxmax(0, 0);
    Vec2i bboxmin(width - 1, height - 1);
    Vec2i clamp(width - 1, height - 1);
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            bboxmin[j] = std::max(0, std::max(bboxmin[i][j], points[i][j]));
            bboxmax[j] = std::max(clamp[j], std::max(bboxmax[i][j], points[i][j]));
        }
    }

    //scan line
    Vec2i p;
    for(p.y = bboxmin.y; p.y <= bboxmax.y; ++p.y)
    {
        for(p.x = bboxmin.x; p.x <= bboxmax.y; ++p.x)
        {
            Vec3f bc = barycentric(points, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) continue;

            image.set(p.x, p.y, color);
        }
    }
}