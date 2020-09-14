#include <algorithm>

#include "Bounds.h"

XRender::Bounds::Bounds()
{
    center = Vec3f_Zero;
    extents = Vec3f_Zero;
}

XRender::Bounds::Bounds(const Vec3f min, const Vec3f max)
{
    center = (min + max) / 2;
    extents = (max - min) / 2;

    if(extents.x < 0) extents.x = 0;
    if(extents.y < 0) extents.y = 0;
    if(extents.z < 0) extents.z = 0;
}

void XRender::Bounds::Expand(const Vec3f& point)
{
    Vec3f distance = point - center;
    Vec2f ex = ExpandAxis(distance.x, extents.x);
    center.x += ex.x;
    extents.x += ex.y;
    
    ex = ExpandAxis(distance.y, extents.y);
    center.y += ex.x;
    extents.y += ex.y;
    
    ex = ExpandAxis(distance.z, extents.z);
    center.z += ex.x;
    extents.z += ex.y;
}
       
void XRender::Bounds::Expand(const Bounds& bounds)
{
    Vec3f min = bounds.center - bounds.extents;
    Vec3f max = bounds.center + bounds.extents;

    Expand(min);
    Expand(max);
}

void XRender::Bounds::Zero()
{
    center = Vec3f_Zero;
    extents = Vec3f_Zero;
}

Vec2f XRender::Bounds::ExpandAxis(const float& distance, const float& extent_axis)
{
    Vec2f ret;
    if(distance > extent_axis)
    {
        float extent = (distance - extent_axis) / 2;
        ret.x = extent;
        ret.y = extent;
    }
    else if(distance < extent_axis)
    {
        float extent = (distance - extent_axis) / 2;
        ret.x = extent;
        ret.y = -extent;
    }

    return ret;
}