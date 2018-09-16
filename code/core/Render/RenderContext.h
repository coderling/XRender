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

    void Init(const int w, const int h)
    {
        if(m_renderSurface == nullptr)
        {
            m_width = w; m_height = h;
            CreateRenderSurface();
        }
    }

    void Releae()
    {
        if(m_renderSurface != nullptr)
        {
            SDL_FreeSurface(m_renderSurface);
            m_renderSurface = nullptr;
        }
    }

    void Lock()
    {

        if(SDL_MUSTLOCK(m_renderSurface))
        {
            SDL_LockSurface(m_renderSurface);
        } 
    }

    void UnLock()
    {
        if(SDL_MUSTLOCK(m_renderSurface))
        {
            SDL_UnlockSurface(m_renderSurface);
        }
    }

    inline SDL_Surface* GetSurface(){ return m_renderSurface; }

private:
    SDL_Surface* m_renderSurface;

    inline void CreateRenderSurface()
    {
        Uint32 rmask, gmask, bmask, amask;
        /* SDL interprets each pixel as a 32-bit number, so our masks must depend
        on the endianness (byte order) of the machine */
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
        #else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
        #endif
            m_renderSurface = SDL_CreateRGBSurface(0, m_width, m_height, 32, rmask,
                                          gmask, bmask, amask);
  }
};
