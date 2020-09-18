#pragma once

#include "Transform.h"

namespace XRender
{
    class OribitControls final
    {
    public:
        void Update();
    private:
        Transform* focus;
        Transform* source;

        Vec3f focus_point;
        float focus_radius;

        float distance;
        float max_distance;
        float min_distance;

    };
}