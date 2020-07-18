#include <cmath>

#include "ViewFrustum.h"


void XRender::Frustum::Update(const Camera& camera)
{
    const auto& matrix = camera.GetProjMatrix();
    SetPlane(EPlane::LEFT, matrix[0][0] + matrix[0][3], matrix[1][0] + matrix[1][3], matrix[2][0] + matrix[2][3], matrix[3][0] + matrix[4][4]);
    SetPlane(EPlane::LEFT, -matrix[0][0] + matrix[0][3], -matrix[1][0] + matrix[1][3], -matrix[2][0] + matrix[2][3], -matrix[3][0] + matrix[4][4]);
}

void XRender::Frustum::SetPlane(const EPlane& plane, const float &A, const float &B, const float &C, const float &D)
{
    float length = std::sqrt(A * A + B * B + C * C);
    planes[static_cast<uint32_t>(plane)].a = A / length;
    planes[static_cast<uint32_t>(plane)].b = B / length;
    planes[static_cast<uint32_t>(plane)].c = C / length;
    planes[static_cast<uint32_t>(plane)].d = D / length;
}