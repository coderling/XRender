#include <cassert>

#include "Texture2D.h"

void XRender::Texture2D::Create(const uint32_t& width, const uint32_t& height)
{
    this->width = width;
    this->height = height;
    CreateBuffer(width * height);
}
        
const uint32_t& XRender::Texture2D::GetWidth() const
{
    return this->width;
}

const uint32_t& XRender::Texture2D::GetHeight() const
{
    return this->width;
}

void XRender::Texture2D::SetColor(const uint32_t& x, const uint32_t& y, const XRender::Color& color)
{
    Texture::SetColor(width * y + x, color);
}

XRender::Color XRender::Texture2D::GetColor(const uint32_t& x, const uint32_t& y) const
{
    assert(x < width && y < height);

    return datas[width * y + x];
}