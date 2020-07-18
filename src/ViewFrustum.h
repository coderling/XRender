#pragma once

#include <geometry.h>
#include "Camera.h"

namespace XRender
{
    class Frustum final
    {
    private:
        struct Plane final
        {
            float a;
            float b;
            float c;
            float d;
        };

        enum struct EPlane
        {
            TOP = 0,
            BOTTOM,
            LEFT,
            RIGHT,
            NEAR,
            FAR
        };
    public:
        void Update(const Camera& camera);
        bool PointInFrustum() const;
        bool SphereInFrustum() const;
        bool AABBInFrustum() const;
    private:
        void SetPlane(const EPlane& plane, const float& A, const float& B, const float& C, const float& D);
        Plane planes[6];
    };
}