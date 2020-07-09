#include "Lighting.h"
#include "Graphics.h"

XRender::Lighting::Light::Light():  is_active(false)
{
    data = std::make_unique<XRender::Lighting::LightData>();
}

XRender::Lighting::Light::~Light()
{
    if (is_active)
        Graphics::VirtualGraphic().RemoveLight(data.get());
}

bool XRender::Lighting::Light::IsActive() const
{
    return is_active;
}

void XRender::Lighting::Light::Enable()
{
    if(!is_active)
    {
        is_active = true;
        Graphics::VirtualGraphic().AddLight(data.get());
    }
}

void XRender::Lighting::Light::Disable()
{
    if(is_active)
    {
        Graphics::VirtualGraphic().RemoveLight(data.get());
        is_active = false;
    }
}

XRender::Lighting::LightData* XRender::Lighting::Light::GetData() const
{
    return data.get();
}