#pragma once

#include "../../RenderTarget.h"
#include "tgaimage.h"

namespace XRender
{

    class ImageRenderTarget: public RenderTarget 
    {
    public:
        ImageRenderTarget(const std::string& name);
        ~ImageRenderTarget() override;
        void OnPresent(const RenderContext* context) override;
        void Save();
    private:
        void OnInit() override;
        void ColorToTGAColor(const XRender::Color& color, TGAColor& ret);
        std::unique_ptr<TGAImage> pRtImage = nullptr;
        std::string out_path;
    };

}