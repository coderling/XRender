#pragma once

class Vector3;
class EulerAngles;
class Quaternion;

//简单的3x3矩阵，仅用作旋转
//假设矩阵是正交的，在变换时指定方向

class RotationMatrix
{
public:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;

    //单位化矩阵
    void identity();

    //根据指定方位构造矩阵
    void setup(const EulerAngles& orientation);

    //根据四元素构造矩阵，假设四元素代表指定方向的变换
    void fromInertialToObjectQuaternion(const Quaternion& q);
    void fromObjectToInertailQuaternion(const Quaternion& q);

    //执行旋转
    Vector3 inertialToObject(const Vector3& v) const;
    Vector3 ObjectToinertial(const Vector3& v) const;
};