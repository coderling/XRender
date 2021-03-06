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

    Vec3f RotateToEuler(const Matrix& matrix);
    
    Matrix TransposeMatrix(Vec3f trans);
    
    Matrix ModelMatrix(Vec3f pos, Vec3f scale, Vec3f angle);

    Matrix CameraLookAt(const Vec3f& pos, const Vec3f& up, const Vec3f& look);

    Matrix Perspective(const float& fov, const float& aspect, const float& near, const float& far);
    
    Matrix CaculateOrthgraphic(const float& left, const float& right, const float& bottom, const float& top,
                               const float& near, const float& far);

    bool FloatEqual(const float& lv, const float& rv);

    Vec3f TransformVector(const Matrix m, const Vec3f& vector);
    Vec3f TransformPoint(const Matrix m, const Vec3f& point);
    void TransformPoint(const Matrix m, const Vec3f& point, Vec3f& out);
    
    const float PI = 3.1415926535f;
    const float PI_OVER2 = PI / 2.0f;
    const float PI_DEGREE = PI / 180.0f;
    const float PI_TO_DEGREE = 180.0f / PI;
}