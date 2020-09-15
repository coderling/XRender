#pragma once

#include "../../RenderDevice.h"
#include "tgaimage.h"

namespace XRender
{

    class ImageDevice: public RenderDevice 
    {
    public:
        ImageDevice(const std::string& name);
        ~ImageDevice() override;
        void OnPresent(const RenderContext* context) override;
        void Save();
    private:
        void OnInit() override;
        void OnUpdate() override;
        void ColorToTGAColor(const XRender::Color& color, TGAColor& ret);
        std::unique_ptr<TGAImage> pRtImage = nullptr;
        std::string out_path;
    };

}