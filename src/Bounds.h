#pragma once

#include <geometry.h>

namespace XRender
{
    class Bounds
    {
    public:
        Bounds();
        Bounds(const Vec3f min, const Vec3f max);
        void Expand(const Vec3f& point);
        void Expand(const Bounds& bounds);
        void Zero();
    public:
        Vec3f center;
        Vec3f extents;
    private:
        const Vec2f& ExpandAxis(const float& distance, const float& extent_axis);
    };
}