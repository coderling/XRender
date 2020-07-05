#include <cassert>

#include "Texture2D.h"

XRender::Texture::~Texture()
{
    if(datas != nullptr)
    {
        delete [] datas;
    }
}

void XRender::Texture::SetColor(const uint32_t& index, const Color& color)
{
    assert(index < size);
    datas[index] = color;
}

XRender::Color XRender::Texture::GetColor(const uint32_t& index) const
{
    assert(index < size);
    return datas[index];
}

XRender::Color* XRender::Texture::GetColors() const
{
    return datas;
}

const uint32_t& XRender::Texture::Size() const
{
    return size;
}

void XRender::Texture::SetColors(const std::vector<Color>& colors)
{
    assert(colors.size() < size);
    for(uint32_t index = 0; index < colors.size(); ++index)
    {
        datas[index] = colors[index];
    }
}

void XRender::Texture::CreateBuffer(const uint32_t& size)
{
    this->size = size;
    datas = new Color[size];
}