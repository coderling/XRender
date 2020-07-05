#include "Platform.h"

#ifdef USE_IMAGE_TARGET 
#include "../image/ImageRenderTarget.h"
#elif WIN32
#include "../win/WindowsRenderTarget.h"
#else
#include "../image/ImageRenderTarget.h"
#endif

std::unique_ptr<XRender::RenderTarget> CreateRenderTarget(const std::string& name)
{
    std::unique_ptr<XRender::RenderTarget> ret = nullptr;

    #ifdef USE_IMAGE_TARGET 
    ret.reset(new XRender::ImageRenderTarget(name));
    #elif WIN32
    ret.reset(new XRender::WindowsRenderTarget(name));
    #else
    ret.reset(new XRender::ImageRenderTarget(name));
    #endif
    return ret;
}