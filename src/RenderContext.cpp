#include <cassert>
#include "RenderContext.h"
#include "RenderDevice.h"

static std::unique_ptr<XRender::RenderTexture> default_rendertexture = nullptr;

XRender::RenderContext::RenderContext()
{
}

XRender::RenderContext::~RenderContext()
{
    rendertexture = nullptr;
}

void XRender::RenderContext::ActiveTarget(RenderTexture* rt)
{
    rendertexture = rt;
}

XRender::RenderTexture* XRender::RenderContext::ActivedRenderTexture() const
{
    if(rendertexture == nullptr)
    {
        if(default_rendertexture == nullptr)
        {
            default_rendertexture = RenderTexture::CreateRenderTarget(RenderDevice::Device()->GetWidth(),
                                                                     RenderDevice::Device()->GetHeight(),
                                                                     true, GraphicsEnum::ERenderTargetFormat::Default);
        }
        assert(default_rendertexture != nullptr);
        return default_rendertexture.get();
    }

    assert(rendertexture != nullptr);
    return rendertexture;
}

const uint32_t& XRender::RenderContext::GetWidth() const
{
    return ActivedRenderTexture()->Width();
}

const uint32_t& XRender::RenderContext::GetHeight() const
{
    return ActivedRenderTexture()->Height();
}

void XRender::RenderContext::ClearFrameBuffer()
{
    ClearRenderTargetFrameBuffer(ActivedRenderTexture(), clear_color);
}

void XRender::RenderContext::ClearDepthBuffer()
{
    ClearRenderTargetDepthBuffer(ActivedRenderTexture(), clear_depth);
}