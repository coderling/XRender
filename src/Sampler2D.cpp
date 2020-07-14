#include <cmath>

#include "Sampler2D.h"


void XRender::Sampler2D::AttachTexture(Texture2D * texture)
{
    this->texture = texture;
}
        
XRender::Color XRender::Sampler2D::Point(const float& u, const float& v)
{
    if(texture == nullptr)
    {
        return CColor::GREY;
    }

    uint32_t x = std::lround(u * texture->GetWidth()) % texture->GetWidth();
    uint32_t y = std::lround(v * texture->GetHeight()) % texture->GetHeight();

    return texture->GetColor(x, y);
}