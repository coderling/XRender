#pragma once
#include <cmath>
#include "geometry.h"

Matrix ScaleMatrix(Vec3f scale)
{
    Matrix scaleM = Matrix::identity();
    scaleM[0][0] = scale.x;
    scaleM[1][1] = scale.y;
    scaleM[2][2] = scale.z;
    return scaleM;
}

Matrix RotateMatrix(Vec3f angle)
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

Matrix TransposeMatrix(Vec3f trans)
{
    Matrix transpose = Matrix::identity();
    transpose[0][3] = trans.x;
    transpose[1][3] = trans.y;
    transpose[2][3] = trans.z;

    return transpose;
}

Matrix ModelMatrix(Vec3f pos, Vec3f scale, Vec3f angle)
{
    // 先缩放+旋转+平移
    return TransposeMatrix(pos) * RotateMatrix(angle) * ScaleMatrix(scale);
}

Matrix CameraViewMatrixByLookAt(Vec3f pos, Vec3f up, Vec3f lookAt)
{
    // view = R*T：先平移，再旋转
    // R 由于旋转矩阵是正交矩阵，R=[R-1]转置 --》view = (R-1)转置 * T
    Matrix transpose = Matrix::identity();
    transpose[0][3] = -pos.x;
    transpose[1][3] = -pos.y;
    transpose[1][3] = -pos.z;

    Vec3f lcp = cross(lookAt, up);
    lcp.normalize();
    // 校正up
    up = cross(lcp, lookAt);
    lcp.normalize();
    up.normalize();
    Matrix rotate = Matrix::identity();
    // 先求rotate的转置
    // x ---> lookAt X up
    // y ---> up
    // -z ---> lookAt
    rotate[0][0] = lcp.x;
    rotate[0][1] = lcp.y;
    rotate[0][2] = lcp.z;

    rotate[1][0] = up.x;
    rotate[1][1] = up.y;
    rotate[1][2] = up.z;

    rotate[2][0] = -lookAt.x;
    rotate[2][1] = -lookAt.y;
    rotate[2][2] = -lookAt.z;

    return rotate * transpose;
}

Matrix OrthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
    // 先平移---》缩放到[-1, 1]的立方体内，方便裁剪
    Matrix transpose = Matrix::identity();
    transpose[0][3] = -(left + right) / 2;
    transpose[1][3] = -(bottom + top) / 2;
    transpose[2][3] = -(near + far) / 2;

    float xscale = 2 / (right - left);
    float yscale = 2 / (top - bottom);
    float zscale = 2 / (far - near);
    
    Matrix scaleMatrix = Matrix::identity();
    scaleMatrix[0][0] = xscale;
    scaleMatrix[1][1] = yscale;
    scaleMatrix[2][2] = zscale;

    return scaleMatrix * transpose;
}

Matrix PerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
    // 挤压到正交的视锥体, 再进行正交投影
    Matrix persToOrthMatrix = Matrix::identity();
    persToOrthMatrix[0][0] = near;
    persToOrthMatrix[1][1] = near;
    persToOrthMatrix[2][2] = near + far;
    persToOrthMatrix[2][3] = -near * far;
	persToOrthMatrix[3][2] = 1;
	persToOrthMatrix[3][3] = 0;
    return OrthographicProjectionMatrix(left, right, bottom, top, near, far) * persToOrthMatrix;
}

Matrix PerspectiveProjectionMatrix(float fov, float aspect, float near, float far)
{
    float top = -near * tan(fov * PI / 2.0f / 180.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    return PerspectiveProjectionMatrix(left, right, bottom, top, near, far);
}


Matrix ViewPortMatrix(int x, int y, int w, int h)
{
    Matrix vport = Matrix::identity();
    vport[0][3] = x + w / 2.0f;
    vport[1][3] = x + h / 2.0f;
    vport[2][3] = -255 / 2.0f;
    
    vport[0][0] = w / 2.0f;
    vport[1][1] = h / 2.0f;
    vport[2][2] = -255 / 2.0f;
	return vport;
}