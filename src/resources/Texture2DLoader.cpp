#include <tgaimage.h>
#include <fstream>
#include <iostream>

#include "ILoader.h"

XRender::Res::ILoader<XRender::Texture2D>::ILoader()
{
    const auto& tex_loader = std::bind(&ILoader<Texture2D>::TGALoad, this, std::placeholders::_1, std::placeholders::_2);
    textureLoaders.emplace("tga", tex_loader);
}

std::unique_ptr<XRender::Texture2D> XRender::Res::ILoader<XRender::Texture2D>::Load(const std::string& path)
{
    std::string ext = XRender::Res::FileExtendName(path);
    const auto& iter = textureLoaders.find(ext);
    if(iter != textureLoaders.end())
    {
        std::unique_ptr<XRender::Texture2D> ret = std::make_unique<XRender::Texture2D>();
        iter->second(ret.get(), path);
        return ret;
    }

    return nullptr;
}

void XRender::Res::ILoader<XRender::Texture2D>::UnLoad(std::unique_ptr<Texture2D> res)
{

}

void XRender::Res::ILoader<XRender::Texture2D>::TGALoad(Texture2D* texture, const std::string& path)
{
    TGAImage image;
    image.read_tga_file(path.c_str());
    image.flip_vertically();
    texture->Create(image.get_width(), image.get_height());
    for(uint32_t x = 0; x < image.get_width(); ++x)
    {
        for(uint32_t y =0; y < image.get_height(); ++y)
        {
            auto tga_color = image.get(x, y);
            Color color;
            color.b = tga_color[0] * 1.f / 255;
            color.g = tga_color[1] * 1.f / 255;
            color.r = tga_color[2] * 1.f / 255;
            color.a = tga_color[3] * 1.f / 255;
            texture->SetColor(x, y, color);
        }
    }
}
