#include "Lighting.h"
#include "Graphics.h"

XRender::Lighting::Light::Light():  is_active(false)
{
    data = std::make_unique<XRender::Lighting::LightData>();
    Rotation(Vec3f_Zero);
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

void XRender::Lighting::Light::SetLightType(XRender::Lighting::LightType type)
{
    data->light_type = type;
}

void XRender::Lighting::Light::Position(const Vec3f& position)
{
    transform.SetPosition(position);
    data->position = transform.GetPosition();
}

const XRender::Lighting::LightType& XRender::Lighting::Light::LightType() const
{
    return data->light_type;
}

void XRender::Lighting::Light::Rotation(const Vec3f& rotation)
{
    transform.SetRotation(rotation);
    data->up = transform.Up();
    data->forward = transform.Forward();
}

const XRender::Transform& XRender::Lighting::Light::Transform() const
{
    return transform;
}

void XRender::Lighting::Light::Range(const float& range)
{
    data->range = range;
}

const float& XRender::Lighting::Light::Range() const
{
    return data->range;
}

void XRender::Lighting::Light::Intensity(const float& intensity)
{
    data->intensity = intensity;
}

const float& XRender::Lighting::Light::Intensity() const
{
    return data->intensity;
}

void XRender::Lighting::Light::LightColor(const Color& color)
{
    data->color = color;
}

const XRender::Color& XRender::Lighting::Light::LightColor() const
{
    return data->color;
}