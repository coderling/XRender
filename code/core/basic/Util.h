#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>

extern Uint32 m_wireframeDC;

inline Uint32 HashColor(const SDL_PixelFormat* pf,
                               const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    return SDL_MapRGBA(pf, r, g, b, a);
}

inline Uint32 HashColor(const SDL_PixelFormat* pf, const Uint8 r, const Uint8 g, const Uint8 b)
{
    return SDL_MapRGB(pf, r, g, b);
}

inline void SetWireDrawColor(const SDL_PixelFormat* pf, 
                                    const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    m_wireframeDC = HashColor(pf, r, g, b, a);
}
