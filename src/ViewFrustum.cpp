#include <cmath>

#include "ViewFrustum.h"


void XRender::Frustum::Update(const Camera& camera)
{
    const auto& matrix = camera.GetProjMatrix();
    SetPlane(EPlane::LEFT,  matrix[3][0] + matrix[0][0], matrix[3][1] + matrix[0][1], matrix[3][2] + matrix[0][2], matrix[3][3] + matrix[0][3]);
    SetPlane(EPlane::RIGHT, matrix[3][0] - matrix[0][0], matrix[3][1] - matrix[0][1], matrix[3][2] - matrix[0][2], matrix[3][3] - matrix[0][3]);
    
    SetPlane(EPlane::BOTTOM, matrix[3][0] + matrix[1][0], matrix[3][1] + matrix[1][1], matrix[3][2] + matrix[1][2], matrix[3][3] + matrix[1][3]);
    SetPlane(EPlane::TOP,    matrix[3][0] - matrix[1][0], matrix[3][1] - matrix[1][1], matrix[3][2] - matrix[1][2], matrix[3][3] - matrix[1][3]);
    
    SetPlane(EPlane::NEAR, matrix[3][0] + matrix[2][0], matrix[3][1] + matrix[2][1], matrix[3][2] + matrix[2][2], matrix[3][3] + matrix[2][3]);
    SetPlane(EPlane::FAR,  matrix[3][0] - matrix[2][0], matrix[3][1] - matrix[2][1], matrix[3][2] - matrix[2][2], matrix[3][3] - matrix[2][3]);
}

void XRender::Frustum::SetPlane(const EPlane& plane, const float &A, const float &B, const float &C, const float &D)
{
    float length = std::sqrt(A * A + B * B + C * C);
    planes[static_cast<uint32_t>(plane)].a = A / length;
    planes[static_cast<uint32_t>(plane)].b = B / length;
    planes[static_cast<uint32_t>(plane)].c = C / length;
    planes[static_cast<uint32_t>(plane)].d = D / length;
}

float XRender::Frustum::DistanceToPlane(const uint32_t& plane_index, const Vec3f& point) const
{
    const auto& plane = planes[plane_index];
    return plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d;
}

XRender::Frustum::EState XRender::Frustum::PointInFrustum(const Vec3f& point) const
{
    for(uint32_t pindex = 0; pindex < 6; ++pindex)
    {
        if(DistanceToPlane(pindex, point) < 0)
        {
            return OUTSIDE;
        }
    }
    return INSIDE;
}

XRender::Frustum::EState XRender::Frustum::SphereInFrustum(const Vec3f& point, const float& radius) const
{

    for(uint32_t pindex = 0; pindex < 6; ++pindex)
    {
        const auto& distance = DistanceToPlane(pindex, point);
        if(distance < -radius )
        {
            return OUTSIDE;
        }
        else if(distance < radius)
        {
            return INTERSECT;
        }
    }
    return INSIDE;
}