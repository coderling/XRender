#pragma once

#include <geometry.h>

#include "Bounds.h"

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
            ETOP = 0,
            EBOTTOM,
            ELEFT,
            ERIGHT,
            ENEAR,
            EFAR,
        };

    public:
        void Update(const Matrix& matrix);
        EState PointInFrustum(const Vec3f& point) const;
        EState SphereInFrustum(const Vec3f& pos, const float& radius) const;
        EState AABBInFrustum(const Bounds& bounds) const;
    private:
        void SetPlane(const EPlane& plane, const float& A, const float& B, const float& C, const float& D);
        float DistanceToPlane(const uint32_t& plane_index, const Vec3f& point) const;
        Plane planes[6];
    };
}