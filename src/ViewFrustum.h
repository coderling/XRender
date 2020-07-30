#pragma once

#include <geometry.h>
#include "Camera.h"

namespace XRender
{
    class Frustum final
    {
    public:
        enum EState
        {
            INSIDE = 0,
            INTERSECT,
            OUTSIDE,
        };
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
        EState PointInFrustum(const Vec3f& point) const;
        EState SphereInFrustum(const Vec3f& pos, const float& radius) const;
        //bool AABBInFrustum() const;
    private:
        void SetPlane(const EPlane& plane, const float& A, const float& B, const float& C, const float& D);
        float DistanceToPlane(const uint32_t& plane_index, const Vec3f& point) const;
        Plane planes[6];
    };
}