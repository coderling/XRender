#include <cmath>
#include <cassert>

#include "ImageRenderTarget.h"

XRender::ImageRenderTarget::ImageRenderTarget(const std::string& name):XRender::RenderTarget::RenderTarget(name)
{
    out_path = "";
    out_path.append("ImageOut/");
    out_path.append(name);
    out_path.append(".tga");
}

XRender::ImageRenderTarget::~ImageRenderTarget()
{

}

void XRender::ImageRenderTarget::Save()
{
    pRtImage->write_tga_file(out_path.c_str());
}

void XRender::ImageRenderTarget::OnPresent(const RenderContext* context)
{
    auto frame_buffer = context->GetBuffer();
    assert(frame_buffer != nullptr);
    uint32_t index;
    uint32_t buffer_index = 0;
    TGAColor color;
    for(uint32_t y = 0; y < height; ++y)
    {
        uint32_t cy = height - y - 1;
        for(uint32_t x = 0; x < width; ++x)
        {
            index = y * width + x;
            buffer_index = cy * width + x;
            ColorToTGAColor(frame_buffer[buffer_index], color);
            pRtImage->set(x, y, color);
        }
    }
    Save();
}

void XRender::ImageRenderTarget::OnInit()
{
    pRtImage = std::make_unique<TGAImage>(width, height, TGAImage::RGB);
}

void XRender::ImageRenderTarget::OnUpdate()
{

}


void XRender::ImageRenderTarget::ColorToTGAColor(const XRender::Color& color, TGAColor& ret)
{
    ret[2] = static_cast<unsigned char>(std::round(color.r * 255));
    ret[1] = static_cast<unsigned char>(std::round(color.g * 255));
    ret[0] = static_cast<unsigned char>(std::round(color.b * 255));
    ret[3] = static_cast<unsigned char>(std::round(color.a * 255));
}

