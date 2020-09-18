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

void XRender::Lighting::Light::SetLightType(XRender::Lighting::LightType type)
{
    light_type = type;
    data->world_pos.w = light_type == LightType::Directional ? 0 : 1;
}

void XRender::Lighting::Light::Position(const Vec3f& position)
{
    transform.SetPosition(position);
    if(light_type != LightType::Directional)
    {
        data->world_pos.x = position.x;
        data->world_pos.y = position.y;
        data->world_pos.z = position.z;
    }
    data->position = transform.GetPosition();
}

const XRender::Lighting::LightType& XRender::Lighting::Light::LightType() const
{
    return light_type;
}

void XRender::Lighting::Light::Rotation(const Vec3f& rotation)
{
    transform.SetRotation(rotation);
    if(light_type == LightType::Directional)
    {
        const auto& forward = transform.Forward();
        data->world_pos.x = forward.x;
        data->world_pos.y = forward.y;
        data->world_pos.z = forward.z;
    }

    data->up = transform.Up();
    data->forward = transform.Forward();
}

const XRender::Transform& XRender::Lighting::Light::Transform() const
{
    return transform;
}