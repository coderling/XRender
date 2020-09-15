#pragma once

#include "Color.h"
#include "RenderTexture.h"

namespace XRender
{

class RenderContext final
{
public:
    RenderContext();
    ~RenderContext();
    void ActiveTarget(RenderTexture* rt);
    RenderTexture* ActivedRenderTexture() const;
    const uint32_t& GetWidth() const;
    const uint32_t& GetHeight() const;
    void ClearFrameBuffer();
    void ClearDepthBuffer();
public:
    Color clear_color = XRender::CColor::BLUE;
    float clear_depth = 1;
private:
    
    RenderTexture* rendertexture = nullptr;
};

}