#include <cmath>
#include <cassert>

#include "ImageRenderTarget.h"

XRender::ImageRenderTarget::~ImageRenderTarget()
{

}

void XRender::ImageRenderTarget::OnPresent(const Color *frame_buffer)
{
    assert(frame_buffer != nullptr);
    uint32_t index;
    for(uint32_t x = 0; x < width; x++)
    {
        for(uint32_t y = 0; y < height; y++)
        {
            index = width * y + x;
            pRtImage->set(x, y, ColorToTGAColor(frame_buffer[index]));
        }
    }
}

void XRender::ImageRenderTarget::OnInit()
{
    pRtImage = std::make_unique<TGAImage>(width, height, TGAImage::RGB);
}


TGAColor XRender::ImageRenderTarget::ColorToTGAColor(const XRender::Color& color)
{
    unsigned char r, g, b, a;
    r = static_cast<unsigned char>(std::round(color.r * 255));
    g = static_cast<unsigned char>(std::round(color.g * 255));
    b = static_cast<unsigned char>(std::round(color.b * 255));
    a = static_cast<unsigned char>(std::round(color.a * 255));
    return TGAColor(r, g, b, a);
}

