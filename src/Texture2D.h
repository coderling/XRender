#pragma once

#include "Texture.h"
#include "Color.h"

namespace XRender
{
    class Texture2D: public Texture
    {
    public:
        void Create(const uint32_t& width, const uint32_t& height);
        const uint32_t& GetWidth() const;
        const uint32_t& GetHeight() const;
        void SetColor(const uint32_t& x, const uint32_t& y, const Color& color);
        Color GetColor(const uint32_t& x, const uint32_t& y) const;
    protected:
        uint32_t width;
        uint32_t height;
    };

}
