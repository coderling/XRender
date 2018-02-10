#pragma once

//相对于RotationMatrix的特殊性，Matrix4x3是一个一般化的矩阵
//可以包含多种变换，组合

class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;

class Matrix4x3
{
public:
    //矩阵的值
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz; //代表平移

    //单位化
    void identity();

    //直接访问平移部分
    void zeroTranslation();
    void setTranslation(const Vector3& d);
    void setupTranslation(const Vector3& d);

    //构造执行父空间<->局部空间变换的矩阵， 假定局部空间在指定的位置和方位
    void setupLocalToParent(const Vector3& pos, const EulerAngles& orient);
    void setupLocalToParent(const Vector3& pos, const RotationMatrix& orient);
    void setupParentToLocal(const Vector3& pos, const EulerAngles& orient);
    void setupParentToLocal(const Vector3& pos, const RotationMatrix& orient);

    //构造绕坐标轴旋转的矩阵
    void setupRotate(int axis, float theta);

    //构造绕任意坐标轴旋转
    void setupRotate(const Vector3& axis, float theta);

    //构造旋转矩阵，角位移由四元素给出
    void fromQuaternion(const Quaternion &q);

    //构造沿坐标轴缩放的矩阵
    void setupScale(const Vector3& s);

    //构造沿任意轴缩放的矩阵
    void setupScaleAlongAxis(const Vector3& axis, float k);

    //构造切变矩阵
    void setupShear(int axis, float s, float t);

    //构造投影矩阵，投影平面过原点
    void setupProject(const Vector3& n);

    //构造反射矩阵
    void setupReflect(int axis, float k = 0.0f);

    //构造沿任意平面反射的矩阵
    void setupReflect(const Vector3& n);
};

//运算符*,用于变换点或链接矩阵，乘法顺序从左往右沿变换顺序进行
Vector3 operator*(const Vector3& p, const Matrix4x3& m);

Matrix4x3 operator*(const Matrix4x3& a, const Matrix4x3& b);

//运算符*=
Vector3 operator*=(const Vector3& p, const Matrix4x3& m);

Matrix4x3 operator*=(const Matrix4x3& a, const Matrix4x3& b);

//计算3x3部分的行列式
float determinant(const Matrix4x3& m);

//计算矩阵的逆
Matrix4x3 inverse(const Matrix4x3& m);

//提取矩阵平移部分
Vector3 getTranslation(const Matrix4x3& m);

//从父矩阵-》局部矩阵读取位置/方位
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m);

//从局部矩阵-》父矩阵读取位置/方位
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3& m);
