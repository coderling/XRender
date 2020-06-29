#pragma once

#include "Color.h"

namespace XRender
{

class RenderContext final
{
public:
    RenderContext();
    ~RenderContext();
    void Init(const uint32_t& w, const uint32_t& h);
    void SetPixel(const uint32_t& x, const uint32_t& y, const Color& color);
    const Color& ReadPixel(const uint32_t& x, const uint32_t& y) const;
    const Color* GetBuffer() const;
    void SetDepthBuffer(const uint32_t& x, const uint32_t& y, const float& v);
    float GetDepthBuffer(const uint32_t& x, const uint32_t& y);
    const uint32_t& GetWidth() const;
    const uint32_t& GetHeight() const;
    void ClearFrameBuffer(const XRender::Color& color);
    void ClearDepthBuffer(const float& depth);
private:
    uint32_t GetIndex(const uint32_t& x, const uint32_t& y) const;

    uint32_t width = 400;
    uint32_t height = 400;
    Color* frame_buffer;
    float* depth_buffer;
};

}