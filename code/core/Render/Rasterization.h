/*
 * File: Util
 * File Created: Tuesday, 23rd October 2018 11:50:01 pm
 * Author: coderling (coderling@gmail.com)
 */

#pragma once
#include "code/core/math/Vector3.h"
#include <vector>
#include "Shader.h"
#include "RenderContext.h"
#include "code/core/math/RMath.h"
#include <iostream>

struct Segment_t
{
public:
    VertOut start;
    VertOut end;   
}; 

struct Trapezoidal_t
{
public:
    float top;
    float bottom;
    Segment_t left;
    Segment_t right;
};



static Color& LerpColor(const Color& c1, const Color& c2, float t)
{
    Color r;
    r.r = Lerp(c1.r, c2.r, t);
    r.g = Lerp(c1.g, c2.g, t);
    r.b = Lerp(c1.b, c2.b, t);
    r.a = Lerp(c1.a, c2.a, t);
    return r;
}

static Texcoord LerpTexcoord(const Texcoord &t1, const Texcoord &t2, float t)
{
    Texcoord rt;
    rt.u = Lerp(t1.u, t2.u, t);
    rt.v = Lerp(t1.v, t2.v, t);
    return rt;
}


//sample cvv cull 
bool Check_CVV(const Vector3& p, const float& w)
{
    //x [-1, 1] y[-1, 1] z[0, 1]
    if(p.x < -w || p.x > w
    || p.y < -w || p.y > w
    || p.z < 0 || p.z > w)
    {
        return false;
    }

    return true;
}

//透视除法，并得到屏幕坐标, 屏幕坐标左上角为（0， 0）右下角为（w,h）
void IdentityToDevice(const RenderContext& context, Vector3& p, float w)
{
    float tw = 1.0f / w;
    //
    p.x = (p.x * tw + 1) * 0.5f * context.m_width;
    p.y = (1 - p.y * tw) * 0.5f * context.m_height;
    p.z = p.z * tw;
}


//division a triangle return 0-2 trapezoidal
void DivisionTriangle(const VertOut& v1, const VertOut& v2, const VertOut& v3, std::vector<Trapezoidal_t>& traps)
{
    traps.empty();
    // make p1.y >= p2.y >= p3.y
    const VertOut* p1 = &v1;
    const VertOut* p2 = &v2;
    const VertOut* p3 = &v3;
    const VertOut* tp;
    if(p1->pos.y < p2->pos.y)
    {
        tp = p1; p1 = p2; p2 = tp;
    }

    if(p1->pos.y < p3->pos.y)
    {
        tp = p1; p1 = p3; p3 = tp;
    }

    if(p2->pos.y < p3->pos.y)
    {
        tp = p2; p2 = p3; p3 = tp;
    }

    //line
    if(p1->pos.y == p2->pos.y && p2->pos.y == p3->pos.y) return;
    if(p1->pos.x == p2->pos.x && p2->pos.x == p3->pos.x) return;


    if(p1->pos.y == p2->pos.y)
    {
        //up triangle
        //make p1.x < p2.x
        if(p1->pos.x > p2->pos.x)
        {
            tp = p1; p1 = p2; p2 = tp;
        }

        Trapezoidal_t trap;
        trap.top = p3->pos.y;
        trap.bottom = p1->pos.y;
        trap.left.start = *p3;
        trap.left.end = *p1;
        trap.right.start = *p3;
        trap.right.end = *p2;
        traps.push_back(trap);
        return;
    }
    else if(p2->pos.y == p3->pos.y)
    {
        //down triangle
        //maek p2.x < p3.x
        if(p2->pos.x > p3->pos.x)
        {
            tp = p2; p2 = p3; p3 = tp;
        }
        Trapezoidal_t trap;
        trap.top = p2->pos.y;
        trap.bottom = p1->pos.y;
        trap.left.start = *p2;
        trap.left.end = *p1;
        trap.right.start = *p3;
        trap.right.end = *p1;
        traps.push_back(trap);
        return;
    }
    
    //divison to two triangle, up and down
    //caculate p one line p1-p3, when p.y = p2.y
    float t = (p2->pos.y - p3->pos.y) / (p1->pos.y - p3->pos.y);
    float px = t * (p1->pos.x - p3->pos.x) + p3->pos.x;

    if(px > p2->pos.x)
    {
        //p2 on right of line p1-p3
        Trapezoidal_t trap0;
        trap0.top = p3->pos.y;
        trap0.bottom = p2->pos.y;
        trap0.left.start = *p3;
        trap0.left.end = *p1;
        trap0.right.start = *p3;
        trap0.right.end = *p2;
        traps.push_back(trap0);

        Trapezoidal_t trap1;
        trap1.top = p2->pos.y;
        trap1.bottom = p1->pos.y;
        trap1.left.start = *p3;
        trap1.left.end = *p1;
        trap1.right.start = *p3;
        trap1.right.end = *p2;
        traps.push_back(trap1);
        return;
    }
    else
    {
        // p2 on left of line p1-p3
        Trapezoidal_t trap0;
        trap0.top = p3->pos.y;
        trap0.bottom = p2->pos.y;
        trap0.left.start = *p3;
        trap0.left.end = *p2;
        trap0.right.start = *p3;
        trap0.right.end = *p1;
        traps.push_back(trap0);

        Trapezoidal_t trap1;
        trap1.top = p2->pos.y;
        trap1.bottom = p1->pos.y;
        trap1.left.start = *p3;
        trap1.left.end = *p2;
        trap1.right.start = *p3;
        trap1.right.end = *p1;
        traps.push_back(trap1);
        return;
   
    }
    return ;
}

//do scanline and lerp color
void ScanLineTrapezoidal(const RenderContext& renderContext, const Trapezoidal_t& trap, std::vector<VertOut>& fragments)
{
    int top = (int)(trap.top + 0.5f);
    int bottom = (int)(trap.bottom + 0.5f);
    int wh = renderContext.m_height;
    int ww = renderContext.m_width;
    float pxl, pxr, t, lz, rz;
    Color lc, rc;
    Texcoord luv, ruv;
    int left, right, linew;
    for(; top < bottom; top++)
    {
        if(top >= 0 && top <= wh)
        {
            t = (top - trap.left.start.pos.y) / (trap.left.end.pos.y - trap.left.start.pos.y);
            pxl = Lerp(trap.left.start.pos.x, trap.left.end.pos.x, t);
            lz = Lerp(trap.left.start.pos.z, trap.left.end.pos.z, t);
            lc = LerpColor(trap.left.start.color, trap.left.end.color, t);
            luv = LerpTexcoord(trap.left.start.tex, trap.left.end.tex, t);

            t = (top - trap.right.start.pos.y) / (trap.right.end.pos.y - trap.right.start.pos.y);
            pxr = Lerp(trap.right.start.pos.x, trap.right.end.pos.x, t);
            rz = Lerp(trap.right.start.pos.z, trap.right.end.pos.z, t);
            rc = LerpColor(trap.right.start.color, trap.right.end.color, t);
            ruv = LerpTexcoord(trap.right.start.tex, trap.right.end.tex, t);

            left = (int)(pxl + 0.5f);
            right = (int)(pxr + 0.5f);

            linew = right - left;
            for(int tx = left;tx < right; tx++)
            {
                if(tx >= 0 && tx < ww)
                {
                    t = (tx - left) * 1.0f / linew;
                    VertOut vt;
                    vt.pos.x = tx;
                    vt.pos.y = top;
                    vt.pos.z = Lerp(lz, rz, t);
                    vt.color = LerpColor(lc, rc, t);
                    vt.tex = LerpTexcoord(luv, ruv, t);
                    fragments.push_back(vt);
                }
            }
        }
    }
}

