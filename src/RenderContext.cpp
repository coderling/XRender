#include <cassert>
#include "RenderContext.h"

XRender::RenderContext::RenderContext()
{
    frame_buffer = nullptr;
    depth_buffer = nullptr;
}

XRender::RenderContext::~RenderContext()
{
    if(frame_buffer != nullptr)
    {
        delete [] frame_buffer;
    }

    if(frame_buffer != nullptr)
    {
        delete [] depth_buffer;
    }
}

void XRender::RenderContext::Init(const uint32_t& w, const uint32_t& h)
{
    width = w;
    height = h;
    frame_buffer = new Color[width * height];
    depth_buffer = new float[width * height];
}

void XRender::RenderContext::SetPixel(const uint32_t &x, const uint32_t &y, const Color &color)
{
    assert(frame_buffer != nullptr);
    if(x >= width || y >= height)
        return;
    
    uint32_t index = GetIndex(x, y);
    frame_buffer[index] = color;
}

const XRender::Color& XRender::RenderContext::ReadPixel(const uint32_t &x, const uint32_t &y) const
{
    return frame_buffer[GetIndex(x, y)];
}

const XRender::Color* XRender::RenderContext::GetBuffer() const
{
    return frame_buffer;
}

void XRender::RenderContext::SetDepthBuffer(const uint32_t &x, const uint32_t &y, const float &v)
{
    if(depth_buffer == nullptr || x >= width || y >= height)
        return;

    uint32_t index = GetIndex(x, y);
    depth_buffer[index] = v;    
}

float XRender::RenderContext::GetDepthBuffer(const uint32_t &x, const uint32_t &y)
{
    if(depth_buffer == nullptr || x >= width || y >= height)
        return 0;

    uint32_t index = GetIndex(x, y);
    return depth_buffer[index];
}

const uint32_t& XRender::RenderContext::GetWidth() const
{
    return width;
}

const uint32_t& XRender::RenderContext::GetHeight() const
{
    return height;
}

uint32_t XRender::RenderContext::GetIndex(const uint32_t& x, const uint32_t& y) const
{
    return width * y + x;
}

void XRender::RenderContext::ClearFrameBuffer(const XRender::Color& color)
{
    for(uint32_t x = 0; x < width; ++x)
    {
        for(uint32_t y = 0; y < height; ++y)
        {
            frame_buffer[GetIndex(x, y)] = color;
        }
    }
}

void XRender::RenderContext::ClearDepthBuffer(const float& depth)
{
    for(uint32_t x = 0; x < width; ++x)
    {
        for(uint32_t y = 0; y < height; ++y)
        {
            depth_buffer[GetIndex(x, y)] = depth;
        }
    }
}