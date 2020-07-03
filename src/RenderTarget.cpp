#include "RenderTarget.h"

XRender::RenderTarget::RenderTarget(const std::string& name):name(name), width(0), height(0) {}

XRender::RenderTarget::~RenderTarget()
{

}

void XRender::RenderTarget::Init(const uint32_t &width, const uint32_t &height)
{
    this->width = width;
    this->height = height;
    OnInit();
}

const uint32_t& XRender::RenderTarget::GetWidth() const
{
    return width;
}

const uint32_t& XRender::RenderTarget::GetHeight() const
{
    return height;
}