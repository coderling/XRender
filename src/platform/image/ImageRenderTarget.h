#pragma once

#include "../../RenderTarget.h"
#include "tgaimage.h"

namespace XRender
{

    class ImageRenderTarget: public RenderTarget 
    {
    public:
        ~ImageRenderTarget() override;
        void OnPresent(const Color* frame_buffer) override;
    private:
        void OnInit() override;
        TGAColor ColorToTGAColor(const Color& color);
        std::unique_ptr<TGAImage> pRtImage = nullptr;
    };

}