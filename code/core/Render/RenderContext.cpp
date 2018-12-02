#include "RenderContext.h"
#include <math.h>
#include "code/core/primitive/PrimitiveUtil.h"

void RenderContext::Lock()
{
    if(SDL_MUSTLOCK(m_renderSurface))
    {
        SDL_LockSurface(m_renderSurface);
    } 
}

void RenderContext::UnLock()
{
    if(SDL_MUSTLOCK(m_renderSurface))
    {
        SDL_UnlockSurface(m_renderSurface);
    }
}

void RenderContext::DrawPixel(const int &x, const int &y, const float& depth, const Color &color) {
    auto ind = y * m_renderSurface->w + x;
    if(m_zbuffer[ind] < depth)
    {
        return;
    }

    auto pixels = (Uint32 *)m_renderSurface->pixels;
    pixels[ind] =
     HashColor(m_renderSurface->format, color.r, color.g, color.b, color.a);
     m_zbuffer[ind] = depth;
}

void RenderContext::DrawLine(const int &x1, const int &y1, const int &x2, const int &y2)
{
    XPoint p1, p2;
    p1.x = x1, p1.y = y1;
    p2.x = x2, p2.y = y2;
    DrawLineBresenham(m_renderSurface, p1, p2);
}

void RenderContext::Init(const int w, const int h)
{
    if(m_renderSurface == nullptr)
    {
        m_width = w; m_height = h;
        m_renderSurface = CreateSurface(w, h);
    }

    if(m_defaultTex == nullptr)
    {
        m_defaultTex = CreateSurface(256, 256);
        auto pixels = (Uint32 *)m_defaultTex->pixels;
        Uint32 white = HashColor(m_defaultTex->format, 255, 255, 255, 255); 
        Uint32 black = HashColor(m_defaultTex->format, 0, 0, 0, 255);
        
        for(int i = 0; i < 256; i++)
        {
            for(int j = 0; j < 256; j++)
            {
                int f1 = (i / 16) % 2;
                int f2 = (j / 16) % 2;
                if(f1 == f2)
                {
                    pixels[i * 256 + j] = white;
                }
                else
                {
                    pixels[i * 256 + j] = black;
                }
            }
        }
    }

    if(m_zbuffer == nullptr)
    {
        m_zbuffer = new float[w*h]{99};
    }

    SetWireDrawColor(m_renderSurface->format, 0, 0, 0, 255);
}

void RenderContext::Clear()
{
    SDL_FillRect(m_renderSurface, NULL, SDL_MapRGB(m_renderSurface->format, 0, 85, 255));
    int maxI = m_renderSurface->w * m_renderSurface->h;
    for(int i = 0; i < maxI; ++i)
    {
        m_zbuffer[i] = 99;
    }
}

static inline int SuarateXY(int v, int x, int y)
{
    if( v < x)
    {
        v = x;
    } 
    else if( v > y)
    {
        v = y; 
    }

    return v;
}

SDL_Surface* RenderContext::m_defaultTex = nullptr;

Color RenderContext::SampleDefaultTex(float u, float v)
{
    int tw, th;
    tw = th = 256;

    int x = u * tw + 0.5f;
    int y = v * th + 0.5f;
    x = SuarateXY(x, 0, 255);
    y = SuarateXY(y, 0, 255);
    
    auto pixels = (Uint32 *)m_defaultTex->pixels;
    Color c;
    SDL_GetRGBA(pixels[x * 256 + y], m_defaultTex->format, &c.r, &c.g, &c.b, &c.a);
    return c;
}

void RenderContext::Releae()
{
    if(m_renderSurface != nullptr)
    {
        SDL_FreeSurface(m_renderSurface);
        m_renderSurface = nullptr;
    }

    if(m_defaultTex != nullptr)
    {
        SDL_FreeSurface(m_defaultTex);
        m_defaultTex = nullptr;
    }

    if(m_zbuffer != nullptr)
    {
        delete[] m_zbuffer;
        m_zbuffer = nullptr;
    }
}

SDL_Surface* RenderContext::CreateSurface(int w, int h)
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
        return SDL_CreateRGBSurface(0, w, h, 32, rmask,
                                        gmask, bmask, amask);
}

