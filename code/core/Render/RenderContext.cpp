#include "RenderContext.h"
#include <math.h>


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

void RenderContext::DrawPixel(const int &x, const int &y, const Color &color) {
    auto pixels = (Uint32 *)m_renderSurface->pixels;
    auto ind = y * m_renderSurface->w + x;
    pixels[ind] =
     HashColor(m_renderSurface->format, color.r, color.g, color.b, color.a);
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
                int flag = (i * 16 + j / 16) % 2;
                int rf = i % 2;
                if(flag == rf)
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
    x = SuarateXY(x, 0, 256);
    y = SuarateXY(y, 0, 256);
    
    auto pixels = (Uint32 *)m_defaultTex->pixels;
    Color c;
    SDL_GetRGBA(pixels[x * tw + y], m_defaultTex->format, &c.r, &c.g, &c.b, &c.a);
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

