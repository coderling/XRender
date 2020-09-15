#include "RenderDevice.h"
#include "platform/common/Platform.h"

XRender::RenderDevice::RenderDevice(const std::string& name): width(0), height(0),name(name) {}

XRender::RenderDevice::~RenderDevice()
{

}

void XRender::RenderDevice::Init(const uint32_t &width, const uint32_t &height)
{
    this->width = width;
    this->height = height;
    OnInit();
}

const uint32_t& XRender::RenderDevice::GetWidth() const
{
    return width;
}

const uint32_t& XRender::RenderDevice::GetHeight() const
{
    return height;
}


static std::unique_ptr<XRender::RenderDevice> device = nullptr;
void XRender::RenderDevice::Setup(const std::string& name)
{
    if (device == nullptr)
        device = std::make_unique<DeviceType>(name);
}

XRender::RenderDevice* XRender::RenderDevice::Device()
{
    return device.get();
}
