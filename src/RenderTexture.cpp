#include <cmath>
#include <functional>
#include <unordered_map>
#include <algorithm>

#include "GraphicsEnum.h"
#include "RenderTexture.h"

XRender::RenderTexture::~RenderTexture(){

}

void XRender::RenderTexture::CreateBuffer()
{
    switch (format) 
    {
        case GraphicsEnum::ERenderTargetFormat::ShadowMap:
            num_bytes = 0;
            this->depth = true;
            break;
        default:
            num_bytes = 4; // 4 rgba + depth
            break;
    }

    if(num_bytes > 0)
    {
        uint8_t* bytes = new uint8_t[width * height * num_bytes];
        buffer.reset(bytes);
    }
    if(this->depth)
    {
        float* dbuffer = new float[width * height];
        depth_buffer.reset(dbuffer);
    }
}

XRender::RenderTexture::RenderTexture(const uint32_t& w, const uint32_t& h, const bool& depth, const GraphicsEnum::ERenderTargetFormat& format)
: width(w), height(h), format(format), depth(depth)
{
    CreateBuffer();
}

const uint32_t& XRender::RenderTexture::Width()const
{
    return width;
}

const uint32_t& XRender::RenderTexture::Height() const
{
    return height;
}
        
uint8_t* XRender::RenderTexture::Buffer() const
{
    return buffer.get();
}

float* XRender::RenderTexture::DepthBuffer() const
{
    return depth_buffer.get();
}

const bool& XRender::RenderTexture::Depth() const
{
    return this->depth;
}
 
const uint32_t& XRender::RenderTexture::Bytes() const
{
    return num_bytes; 
}


XRender::RenderDelegate default_render = [](XRender::RenderTexture* target, const uint32_t& x, const uint32_t& y, const XRender::Color& color, const float& depth){
    const auto& t_depth = std::clamp(depth, 0.f, 1.f);
    uint32_t index = (y * target->Width() + x);
    float* depth_buffer = target->DepthBuffer();
    depth_buffer[index] = t_depth;
    
    uint8_t* buffer = target->Buffer();
    if(buffer == nullptr)
        return;
    static XRender::Color32 color32;
    ColorToColor32(color, color32);
    index = index * target->Bytes();
    buffer[index] = color32.r;
    buffer[index + 1] = color32.g;
    buffer[index + 2] = color32.b;
    buffer[index + 3] = color32.a;
};

static std::unordered_map<XRender::GraphicsEnum::ERenderTargetFormat, XRender::RenderDelegate> render_functions {
    {XRender::GraphicsEnum::ERenderTargetFormat::Default, default_render},
    {XRender::GraphicsEnum::ERenderTargetFormat::ShadowMap, default_render},
};

void XRender::RenderTexture::RenderPixel(const uint32_t& x, const uint32_t& y, const Color& color, const float& depth)
{
    assert(x < width && y < height);
    render_func(this, x, y, color, depth);
}


 XRender::ReadColor32Delegate default_read_color32 = [](const XRender::RenderTexture* target, const uint32_t& x, const uint32_t& y, XRender::Color32& color)
{
    uint8_t* buffer = target->Buffer();
    uint32_t index = (y * target->Width() + x) * target->Bytes();
    color.r = buffer[index];
    color.g = buffer[index + 1];
    color.b = buffer[index + 2];
    color.a = buffer[index + 3];
};

static std::unordered_map<XRender::GraphicsEnum::ERenderTargetFormat, XRender::ReadColor32Delegate> read_color32_functions
{
    {XRender::GraphicsEnum::ERenderTargetFormat::Default, default_read_color32},
};
 
 void XRender::RenderTexture::ReadPixel(const uint32_t& x, const uint32_t& y, Color32& color)
 {
    assert(x < width && y < height);
    read_color32_func(this, x, y, color);
 }
 
 void XRender::RenderTexture::ReadPixel(const uint32_t& x, const uint32_t& y, Color& color)
 {
    static Color32 color32;
    ReadPixel(x, y, color32);
    Color32ToColor(color32, color);
 }



 XRender::ReadDepthDelegate default_read_depth = [](const XRender::RenderTexture* target, const uint32_t& x, const uint32_t& y)
{
    uint32_t index = (y * target->Width() + x) ;
    return target->DepthBuffer()[index];
};

static std::unordered_map<XRender::GraphicsEnum::ERenderTargetFormat, XRender::ReadDepthDelegate> read_depth_functions
{
    {XRender::GraphicsEnum::ERenderTargetFormat::Default, default_read_depth},
    {XRender::GraphicsEnum::ERenderTargetFormat::ShadowMap, default_read_depth},
};


float XRender::RenderTexture::DepthOf(const uint32_t& x, const uint32_t& y)
{
    assert(x < width && y < height);
    return read_depth_func(this, x, y);
}
        
const XRender::GraphicsEnum::ERenderTargetFormat& XRender::RenderTexture::Format() const
{
    return format;
}


 XRender::ClearBuffer32Delegate default_clear_color32 = [](XRender::RenderTexture* target, const XRender::Color32& color32)
{
    const auto& size = target->Width() * target->Height();
    auto buffer = target->Buffer();
    uint32_t real_index = 0;
    const uint32_t bytes = target->Bytes();
    for(uint32_t index = 0; index < size; ++index)
    {
        real_index = index * bytes;
        buffer[real_index] = color32.r;
        buffer[real_index + 1] = color32.g;
        buffer[real_index + 2] = color32.b;
        buffer[real_index + 3] = color32.a;
    }
};

static std::unordered_map<XRender::GraphicsEnum::ERenderTargetFormat, XRender::ClearBuffer32Delegate> clear_color32_functions
{
    {XRender::GraphicsEnum::ERenderTargetFormat::Default, default_clear_color32},
};


void XRender::ClearRenderTargetFrameBuffer(RenderTexture* target, const Color32& color)
{
    assert(clear_color32_functions.count(target->Format()) == 1);
    clear_color32_functions[target->Format()](target, color);
}

void XRender::ClearRenderTargetFrameBuffer(RenderTexture* target, const Color& color)
{
    static XRender::Color32 color32;
    ColorToColor32(color, color32);
    ClearRenderTargetFrameBuffer(target, color32);
}

void XRender::ClearRenderTargetDepthBuffer(RenderTexture* target, const float& depth)
{
    if(!target->Depth())
        return;

    const auto& size = target->Width() * target->Height();
    auto depth_buffer = target->DepthBuffer();
    for(uint32_t index = 0; index < size; ++index)
    {
        depth_buffer[index] = depth;
    }
}

std::unique_ptr<XRender::RenderTexture> XRender::RenderTexture::CreateRenderTarget(const uint32_t& w, const uint32_t& h,
	const bool& depth, const XRender::GraphicsEnum::ERenderTargetFormat& format)
{
	std::unique_ptr<RenderTexture> target;
	target.reset(new XRender::RenderTexture(w, h, depth, format));
    target->render_func = render_functions[format];
    target->read_color32_func = read_color32_functions[format];
    target->read_depth_func = read_depth_functions[format];
	return target;
}