/*
 * Filename: /Users/coderling/Documents/DEVLab/XRender/code/core/Render/RenderContext.h
 * Path: /Users/coderling/Documents/DEVLab/XRender/code/core/Render
 * Created Date: Wednesday, September 12th 2018, 10:41:22 pm
 * Author: coderling
 * 渲染环境
 * Copyright (c) 2018 Your Company
 */

#pragma once

#include <SDL.h>
#include "code/core/basic/Util.h"
#include "code/core/primitive/Vertex.h"
#include "code/core/basic/Util.h"

class RenderContext
{
public:
    int m_width;
    int m_height;
    
    RenderContext()
    {
        m_renderSurface = nullptr;
    }

    ~RenderContext()
    {
    }

    void Init(const int w, const int h);
    
    void Releae();

    void Lock();

    void UnLock();
    
    inline SDL_Surface* GetSurface(){ return m_renderSurface; }

    static Color SampleDefaultTex(float u, float v);

    inline void Clear()
    {
        SDL_FillRect(m_renderSurface, NULL, SDL_MapRGB(m_renderSurface->format, 0, 85, 255));
    }

    void DrawPixel(const int& x, const int& y, const Color& color);
private:
    SDL_Surface* m_renderSurface;
    static SDL_Surface* m_defaultTex;

    SDL_Surface* CreateSurface(int w, int h);
};
