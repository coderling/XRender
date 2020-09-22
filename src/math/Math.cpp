#include <algorithm>
#include <cmath>

#include "Math.h"

std::tuple<float, float, float> XRender::Math::TriangleBarycentric(const Vec2f& point1, const Vec2f& point2, const Vec2f& point3, Vec2f p)
{
    Vec3f v1(point3.x - point1.x, point2.x - point1.x, point1.x - p.x);
    Vec3f v2(point3.y - point1.y, point2.y - point1.y, point1.y - p.y);
    Vec3f u = cross(v1, v2);

    // z < 1 说明v1, v2 共线，返回 < 0
    if(std::abs(u.z) < 1e-2) return std::make_tuple(-1, 1, 1);

    return std::make_tuple(1 - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

std::tuple<Vec2i, Vec2i> XRender::Math::TriangleBoundingBox(const Vec2f& point1, const Vec2f& point2, const Vec2f& point3)
{
    Vec2i lb, rt;
    lb.x = std::floor(std::min(std::min(point1.x, point2.x), point3.x)); 
    lb.y = std::floor(std::min(std::min(point1.y, point2.y), point3.y)); 
    rt.x = std::ceil(std::max(std::max(point1.x, point2.x), point3.x)); 
    rt.y = std::ceil(std::max(std::max(point1.y, point2.y), point3.y)); 
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
    // roll -> pitch -> yaw
    return  rotateY * rotateX * rotateZ ;
}

/* 
CyCz + SySxSz       -CySz + SySxCz      SyCx
CxSz                CxCz                -Sx
-SyCz + CySxSz      SySz + CySxCz       CyCx

Sx == 1 CX == 0 Sy == 0 Cy == 1
Cz -Sz 0
0 0 -1
Sz Cz 0
*/
Vec3f XRender::Math::RotateToEuler(const Matrix& matrix)
{
    Vec3f ret;
    float sin_x = -matrix[1][2];
    if(fabs(sin_x) > 0.99999f)
    {
        ret.x = PI_OVER2 * sin_x;
        ret.z = atan2(matrix[2][0], matrix[2][1]);
        ret.y = 0;
    }
    else
    {
        ret.x = asin(sin_x);
        // tan(y) = Sy/Cy = CxSy / CxCy = matrix[0][2] / matrix[2][2] = atan2(Sy, Cy);
        ret.y = atan2(matrix[0][2], matrix[2][2]);
        // tan(z) = Sz/Cz = CxSz/CxCz = -matrix[1][0] / matrix[1][1] = atan2(Sz, Cz)
        ret.z = atan2(matrix[1][0], matrix[1][1]);
    }

    return ret * PI_TO_DEGREE; 
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

Matrix XRender::Math::CameraLookAt(const Vec3f& pos, const Vec3f& up, const Vec3f& look)
{
    Matrix view = Matrix::identity();
    Vec3f x_axis = cross(up,  look);
    Vec3f y_axis = cross(look, x_axis);
    x_axis.normalize();
    y_axis.normalize();
    Vec3f z_axis = look;
    z_axis.normalize();

    view[0][0] = x_axis.x;
    view[0][1] = x_axis.y;
    view[0][2] = x_axis.z;

    view[1][0] = y_axis.x;
    view[1][1] = y_axis.y;
    view[1][2] = y_axis.z;

    view[2][0] = z_axis.x;
    view[2][1] = z_axis.y;
    view[2][2] = z_axis.z;

    view[0][3] = -(x_axis * pos);
    view[1][3] = -(y_axis * pos);
    view[2][3] = -(z_axis * pos);

    return view;
}

/*
    // 挤压到正交的视锥体, 再进行正交投影
2/(right-left)      0                   0       -(left+right)/(right-left)
0              2/(top-bottom)           0       -(bottom+top)/(top-bottom)
0                   0                -2/(f-n)    -(f+n)/(f-n)
0                   0                   0           1

x

n                   0                   0           0
0                   n                   0           0
0                   0                  n+f         n*f
0                   0                   -1           0

2n/(r-l)            0                   0           0
0                  2n/(t-b)             0           0
0                   0               -(f+n)/(f-n)    2(n*f)/(f-n)
0                   0                   -1           0
*/
Matrix XRender::Math::Perspective(const float& fov, const float& aspect, const float& near, const float& far)
{
    float top = near * tan(fov* PI / 2.0f / 180.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    Matrix p = Matrix::identity();

    p[0][0] = 2 * near / (right - left);
    p[1][1] = 2 * near / (top - bottom);
    p[2][2] = -(far + near) / (far - near);
    p[2][3] = -2 * (near * far) / (far - near);
    p[3][2] = -1;
    p[3][3] = 0;

    Matrix persToOrthMatrix = Matrix::identity();
    persToOrthMatrix[0][0] = near;
    persToOrthMatrix[1][1] = near;
    persToOrthMatrix[2][2] = near + far;
    persToOrthMatrix[2][3] = near * far;
	persToOrthMatrix[3][2] = -1;
	persToOrthMatrix[3][3] = 0;

    const Matrix& orth = CaculateOrthgraphic(left, right, top, bottom, near, far);
    Matrix t = orth * persToOrthMatrix;
    return p;
    return orth * persToOrthMatrix;
}

/*
Orth = Mr * Mt

2/(right-left)      0                   0           0
0               2/(top - bottom)        0           0 
0                   0               -2/(f-n)        0 
0                   0                   0           1

1                   0                   0        -(left+right)/2
0                   1                   0        -(bottom+top)/2
0                   0                   1        (n+f)/2
0                   0                   0           1


2/(right-left)      0                   0       -(left+right)/(right-left)
0              2/(top-bottom)           0       -(bottom+top)/(top-bottom)
0                   0                -2/(f-n)    -(f+n)/(f-n)
0                   0                   0           1

*/
Matrix XRender::Math::CaculateOrthgraphic(const float& left, const float& right, const float& top, const float& bottom,
                               const float& near, const float& far)
{
    assert(far > near && near > 0);
    // 先平移---》缩放到[-1, 1]的立方体内
    Matrix orth = Matrix::identity();
    float width = right - left;
    float height = top - bottom;
    float depth = far - near;

    orth[0][0] = 2 / width;
    orth[1][1] = 2 / height;
    orth[2][2] = -2 / depth;

    orth[0][3] = -(left + right) / width;
    orth[1][3] = -(bottom + top) / height;
    orth[2][3] = -(far + near) / (far - near);
    return orth;
}

bool XRender::Math::FloatEqual(const float& lv, const float& rv)
{
    return std::abs(lv - rv) < 1e-4;
}
    
    
Vec3f XRender::Math::TransformVector(const Matrix m, const Vec3f& vector)
{
    static Vec4f v;
    v.x = vector.x;
    v.y = vector.y;
    v.z = vector.z;
    v.w = 0;
    v = m * v;
    v = v / v.w;

    return embed<3>(v);
}

Vec3f XRender::Math::TransformPoint(const Matrix m, const Vec3f& point)
{
    static Vec4f v;
    v.x = point.x;
    v.y = point.y;
    v.z = point.z;
    v.w = 1;

    v = m * v;
    v = v / v.w;

    return embed<3>(v);
}