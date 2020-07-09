#pragma once

#include <geometry.h>

#include "Color.h"

namespace XRender::Lighting 
{
    struct LightData 
    {
        float range;
        float intensity;
        Vec4f world_pos;
        Color color;
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
    private:
        std::unique_ptr<LightData> data;
        bool is_active;
    };
    
    const uint32_t max_light_num = 4;
    const LightData null_light{0, 0, {0, 0, 0, 0}, {0.5f, 0.5f, 0.5f, 1.f}};
}