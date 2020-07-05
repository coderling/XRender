#include <cmath>

#include "Sampler2D.h"


XRender::Sampler2D::Sampler2D(const Texture2D* texture): texture(texture)
{
}
        
XRender::Color XRender::Sampler2D::Point(const float& u, const float& v)
{
    if(texture == nullptr)
    {
        return CColor::BLACK;
    }

    uint32_t x = std::lround(u * texture->GetWidth()) % texture->GetWidth();
    uint32_t y = std::lround(v * texture->GetHeight()) % texture->GetHeight();

    return texture->GetColor(x, y);
}