#pragma once

#include <memory>
#include <functional>

#include "GraphicsEnum.h"
#include "Color.h"

namespace XRender
{
    class RenderTexture;
    typedef std::function<void(XRender::RenderTexture*, const uint32_t& x, const uint32_t& y, const XRender::Color& color, const float& depth)> RenderDelegate;
	typedef std::function<void(const XRender::RenderTexture* target, const uint32_t& x, const uint32_t& y, XRender::Color32& color)> ReadColor32Delegate;
	typedef std::function<float(const XRender::RenderTexture* target, const uint32_t& x, const uint32_t& y)> ReadDepthDelegate;
	typedef std::function<void(XRender::RenderTexture* target, const XRender::Color32& color)> ClearBuffer32Delegate;

    class RenderTexture final
    {
    public:

        static std::unique_ptr<RenderTexture> CreateRenderTarget(const uint32_t& w, const uint32_t& h,
                                                                const bool& depth, const GraphicsEnum::ERenderTargetFormat& format);
        ~RenderTexture();
        const uint32_t& Width()const;
        const uint32_t& Height() const;
        void RenderPixel(const uint32_t& x, const uint32_t& y, const Color& color, const float& depth);
        void ReadPixel(const uint32_t& x, const uint32_t& y, Color& color);
        void ReadPixel(const uint32_t& x, const uint32_t& y, Color32& color);
        float DepthOf(const uint32_t& x, const uint32_t& y);
        const GraphicsEnum::ERenderTargetFormat& Format() const;
        uint8_t* Buffer() const;
        float* DepthBuffer() const;
        const bool& Depth() const;
        const uint32_t& Bytes() const;
    private:
        RenderTexture(const uint32_t& w, const uint32_t& h, const bool& depth, const GraphicsEnum::ERenderTargetFormat& format);
        void CreateBuffer();
        uint32_t width = 0;
        uint32_t height = 0;
        GraphicsEnum::ERenderTargetFormat format;
        bool depth = false;
        std::unique_ptr<uint8_t> buffer = nullptr;
        std::unique_ptr<float> depth_buffer = nullptr;
        uint32_t num_bytes;
        RenderDelegate render_func;
        ReadColor32Delegate read_color32_func;
        ReadDepthDelegate read_depth_func;
    };
	
    void ClearRenderTargetFrameBuffer(RenderTexture* target, const Color& color);
    void ClearRenderTargetFrameBuffer(RenderTexture* target, const Color32& color);
    void ClearRenderTargetDepthBuffer(RenderTexture* target, const float& depth);
    
}