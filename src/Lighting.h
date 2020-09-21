#pragma once

#include <geometry.h>

#include "Color.h"
#include "Transform.h"

namespace XRender::Lighting 
{
    enum struct LightType
    {
        Directional,
        Point,
    };

    struct LightData 
    {
        float range;
        float intensity;
        Color color;
        Vec3f forward;
        LightType light_type;
        Vec3f up;
        Vec3f position;
    };

    class Light final
    {
    public:
        Light();
        ~Light();
        bool IsActive() const;
        void Enable();
        void Disable();
        void Range(const float& range);
        const float& Range() const;
        void Intensity(const float& intensity);
        const float& Intensity() const;
        void LightColor(const Color& color);
        const Color& LightColor() const;
        void SetLightType(LightType type);
        void Position(const Vec3f& position);
        void Rotation(const Vec3f& rotation);
        const LightType& LightType() const;
        const Transform& Transform() const;
    private:
        std::unique_ptr<LightData> data;
        bool is_active;
        XRender::Transform transform;
    };
    
    const uint32_t max_light_num = 4;
}