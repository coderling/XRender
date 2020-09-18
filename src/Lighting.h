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
    private:
        Vec4f world_pos;
        Vec3f up;
        Vec3f forward;
        Vec3f position;
        friend class ShadowMap;
        friend class Light;
    };

    class Light final
    {
    public:
        Light();
        ~Light();
        bool IsActive() const;
        void Enable();
        void Disable();
        LightData* GetData() const;
        void SetLightType(LightType type);
        void Position(const Vec3f& position);
        void Rotation(const Vec3f& rotation);
        const LightType& LightType() const;
        const Transform& Transform() const;
    private:
        std::unique_ptr<LightData> data;
        bool is_active;
        XRender::Transform transform;
        Lighting::LightType light_type;
    };
    
    const uint32_t max_light_num = 4;
}