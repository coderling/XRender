#include <cmath>
#include <cassert>

#include "ImageDevice.h"

XRender::ImageDevice::ImageDevice(const std::string& name):XRender::RenderDevice::RenderDevice(name)
{
    out_path = "";
    out_path.append("ImageOut/");
    out_path.append(name);
    out_path.append(".tga");
}

XRender::ImageDevice::~ImageDevice()
{

}

void XRender::ImageDevice::Save()
{
    pRtImage->write_tga_file(out_path.c_str());
}

void XRender::ImageDevice::OnPresent(const RenderContext* context)
{
    auto rendertexture = context->ActivedRenderTexture();
    uint32_t buffer_index = 0;
    TGAColor color;
    Color scolor;
    for(uint32_t y = 0; y < height; ++y)
    {
        uint32_t cy = height - y - 1;
        for(uint32_t x = 0; x < width; ++x)
        {
            buffer_index = cy * width + x;
            rendertexture->ReadPixel(x, y, scolor);
            ColorToTGAColor(scolor, color);
            pRtImage->set(x, y, color);
        }
    }
    Save();
}

void XRender::ImageDevice::OnInit()
{
    pRtImage = std::make_unique<TGAImage>(width, height, TGAImage::RGB);
}

void XRender::ImageDevice::OnUpdate()
{

}


void XRender::ImageDevice::ColorToTGAColor(const XRender::Color& color, TGAColor& ret)
{
    ret[2] = static_cast<unsigned char>(std::round(color.r * 255));
    ret[1] = static_cast<unsigned char>(std::round(color.g * 255));
    ret[0] = static_cast<unsigned char>(std::round(color.b * 255));
    ret[3] = static_cast<unsigned char>(std::round(color.a * 255));
}

