#pragma once

#include <geometry.h>

namespace XRender
{
    class Bounds
    {
    public:
        Bounds();
        Bounds(const Vec3f& min, const Vec3f& max);
        void Expand(const Vec3f& point);
        void Expand(const Bounds& bounds);
        void Zero();
        Vec3f Max() const;
        Vec3f Min() const;
        void SetWithMinMax(const Vec3f& min, const Vec3f& max);
    public:
        Vec3f center;
        Vec3f extents;
    };
}