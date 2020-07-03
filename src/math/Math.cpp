#include <algorithm>
#include "Math.h"

std::tuple<float, float, float> XRender::Math::TriangleBarycentric(const Vec2f& point1, const Vec2f& point2, const Vec2f& point3, Vec2f p)
{
    Vec3f v1(point3.x - point1.x, point2.x - point1.x, point1.x - p.x);
    Vec3f v2(point3.y - point1.y, point2.y - point1.y, point1.y - p.y);
    Vec3f u = cross(v1, v2);

    // z < 1 说明v1, v2 共线，返回 < 0
    if(std::abs(u.z) < 1) return std::make_tuple(-1, 1, 1);

    return std::make_tuple(1 - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

std::tuple<Vec2i, Vec2i> XRender::Math::TriangleBoundingBox(const Vec3f& point1, const Vec3f& point2, const Vec3f& point3)
{
    Vec2i lb, rt;
    lb.x = std::floor(std::min(std::min(point1.x, point2.x), point3.x)); 
    lb.y = std::floor(std::min(std::min(point1.y, point2.y), point3.y)); 
    rt.x = std::floor(std::max(std::max(point1.x, point2.x), point3.x)); 
    rt.y = std::floor(std::max(std::max(point1.y, point2.y), point3.y)); 
    return std::make_tuple(lb, rt);
}

Matrix XRender::Math::ScaleMatrix(Vec3f scale)
{
    Matrix scaleM = Matrix::identity();
    scaleM[0][0] = scale.x;
    scaleM[1][1] = scale.y;
    scaleM[2][2] = scale.z;
    return scaleM;
}
    
Matrix XRender::Math::RotateMatrix(Vec3f angle)
{
    angle = angle * PI / 180;
    float csx = cos(angle.x);
    float ssx = sin(angle.x);
    float csy = cos(angle.y);
    float ssy = sin(angle.y);
    float csz = cos(angle.z);
    float ssz = sin(angle.z);
    // x-> y -> z 特殊点推导
    Matrix rotateX = Matrix::identity();
    rotateX[1][1] = csx;
    rotateX[1][2] = -ssx;
    rotateX[2][1] = ssx;
    rotateX[2][2] = csx;
    
    Matrix rotateY = Matrix::identity();
    rotateY[0][0] = csy;
    rotateY[0][2] = ssy;
    rotateY[2][0] = -ssy;
    rotateY[2][2] = csy;
    
    Matrix rotateZ = Matrix::identity();
    rotateZ[0][0] = csz;
    rotateZ[0][1] = -ssz;
    rotateZ[1][0] = ssz;
    rotateZ[1][1] = csz;
    return rotateZ * rotateY * rotateX;
}
    
Matrix XRender::Math::TransposeMatrix(Vec3f trans)
{
    Matrix transpose = Matrix::identity();
    transpose[0][3] = trans.x;
    transpose[1][3] = trans.y;
    transpose[2][3] = trans.z;
    
    return transpose;
}
    
Matrix XRender::Math::ModelMatrix(Vec3f pos, Vec3f scale, Vec3f angle)
{
    // 先缩放+旋转+平移
    return TransposeMatrix(pos) * RotateMatrix(angle) * ScaleMatrix(scale);
}