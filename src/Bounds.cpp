#include <algorithm>

#include "Bounds.h"


XRender::Bounds::Bounds()
{
    center = Vec3f_Zero;
    extents = Vec3f_Zero;
}

void XRender::Bounds::SetWithMinMax(const Vec3f& min, const Vec3f& max)
{
    center = (min + max) / 2;
    extents = (max - min) / 2;

    if(extents.x < 0) extents.x = 0;
    if(extents.y < 0) extents.y = 0;
    if(extents.z < 0) extents.z = 0;
}

XRender::Bounds::Bounds(const Vec3f& min, const Vec3f& max)
{
    SetWithMinMax(min, max);
}

void XRender::Bounds::Expand(const Vec3f& point)
{
    Vec3f& min = Min();
    Vec3f& max = Max();
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    min.z = std::min(min.z, point.z);
    
    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
    max.z = std::max(max.z, point.z);
    
    SetWithMinMax(min, max);
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

Vec3f XRender::Bounds::Max() const
{
    return center + extents;
}

Vec3f XRender::Bounds::Min() const
{
    return center - extents;
}