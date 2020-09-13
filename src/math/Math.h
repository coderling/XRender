#pragma once
#include <tuple>
#include <geometry.h>


namespace XRender::Math
{
    std::tuple<float, float, float> TriangleBarycentric(const Vec2f& point1, const Vec2f& point2, const Vec2f& point3, Vec2f p);
    std::tuple<Vec2i, Vec2i> TriangleBoundingBox(const Vec2f& point1, const Vec2f& point2, const Vec2f& point3);

    template<class T>
    T BarycentricInterpolation(const T& proterty1, const T& proterty2, const T& proterty3, const Vec3f& barycentric)
    {
        return proterty1 * barycentric.x + proterty2 * barycentric.y  + proterty3 * barycentric.z;
    }
    
    template<class T>
    inline T LinearInterpolation(const T& proterty1, const T& proterty2, const float& t)
    {
        return proterty1 + (proterty2 - proterty1) * t;
    }


    Matrix ScaleMatrix(Vec3f scale);
    
    Matrix RotateMatrix(Vec3f angle);
    
    Matrix TransposeMatrix(Vec3f trans);
    
    Matrix ModelMatrix(Vec3f pos, Vec3f scale, Vec3f angle);

    inline bool FloatEqual(const float& lv, const float& rv)
    {
        return std::abs(lv - rv) < 1e-4;
    }
}