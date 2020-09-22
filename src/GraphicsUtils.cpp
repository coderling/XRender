#include "GraphicsUtils.h"
#include "Graphics.h"
#include "ShadowMap.h"

void XRender::CopyDepth(float* buffer, const uint32_t& size)
{
    const uint32_t& width = Graphics::VirtualGraphic().GetContextWidth();
    const uint32_t& height = Graphics::VirtualGraphic().GetContextHeight();
    assert(size == width * height);
    auto depth_buffer = Graphics::VirtualGraphic().GetRenderContext()->ActivedRenderTexture()->DepthBuffer();
    for(uint32_t index = 0; index < size; ++index)
    {
        buffer[index] = depth_buffer[index];
    }
}
    
    
float XRender::SampleShadowMap(const float& u, const float& v)
{
    return Lighting::ShadowMap::SampleShadowMap(u, v);
}