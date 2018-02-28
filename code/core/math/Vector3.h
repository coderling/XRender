/**
 * @Date:   2017-10-26 16:34:34
 * @Email:  coderling@gmail.com
 * @Last modified time: 2017-10-26 16:43:00
 * 3D向量类
 */

#pragma once
#include <math.h>

class Vector3
{
public:
    float x, y, z;

    //构造函数
    Vector3(){}

    //复制构造函数
    Vector3(const Vector3& va): x(va.x), y(va.y), z(va.z){}

    Vector3(float nx, float ny, float nz): x(nx), y(ny), z(nz){}

    //赋值操作
    Vector3& operator=(const Vector3 &va)
    {
        x = va.x; y = va.y; z = va.z;
        return *this;
    }

    //const 成员函数，表示函数不会去修改对象
    bool operator==(const Vector3 &va) const
    {
        return x == va.x && y == va.y && z == va.z;
    }

    bool operator!=(const Vector3 &va) const
    {
        return x != va.x || y != va.y || z != va.z;
    }

    //置零
    void zero()
    {
        x = y = z = 0.0f;
    }

    //负号，返回赋值对象
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    //加法运算！
    Vector3 operator+(const Vector3 &va) const
    {
        return Vector3(x + va.x, y + va.y, z + va.z);
    }

    //减法运算
    Vector3 operator-(const Vector3 &va) const
    {
        return Vector3(x - va.x, y - va.y, z - va.z);
    }

    //与标量相乘
    Vector3 operator*(const float va) const
    {
        return Vector3(x * va, y * va, z * va);
    }

    //与标量相除,未对除零进行检查
    Vector3 operator/(const float va) const
    {
        float mul = 1 / va;
        return Vector3(x * mul, y * mul, z * mul);
    }

    //自反运算符
    Vector3& operator+=(const Vector3 &va)
    {
        x += va.x; y += va.y; z += va.z;
        return *this;
    }

    Vector3& operator-=(const Vector3 &va)
    {
        x -= va.x; y -= va.y; z -= va.z;
        return *this;
    }

    Vector3& operator*=(const float va)
    {
        x *= va; y *= va; z *= va;
        return *this;
    }

    Vector3& operator/(const float va)
    {
        x /= va; y /= va; z /=va;
        return *this;
    }

    //向量标准化
    void normalize()
    {
        float magSq = x * x + y * y + z * z;
        if(magSq > 0.0f)
        {
            //避免除0
            float mul = 1.0f / sqrt(magSq);
            x *= mul;
            y *= mul;
            z *= mul;
        }
    }

    //向量点乘，重载标准乘法函数
    float operator*(const Vector3 &va) const
    {
        return x * va.x + y * va.y + z * va.z;
    }
};

////////
//非成员函数
///////

//求模
inline float vectorMag(const Vector3 &va)
{
    return sqrt(va.x * va.x + va.y * va.y + va.z * va.z);
}

//叉乘
inline Vector3 crossProduct(const Vector3 &va, const Vector3 &vb)
{
    // x1 x2
    // y1 y2
    // z1 z2
    return Vector3(
        va.y * vb.z - va.z * vb.y,
        va.z * vb.x - va.x * vb.z,
        va.x * va.y - va.y * vb.x
    );
}

//左乘标量
inline Vector3 operator*(const float k, const Vector3 &va)
{
    return Vector3(k * va.x, k * va.y, k * va.z);
}

//两点间的距离
inline float distance(const Vector3 &va, const Vector3 &vb)
{
    float dx = va.x - vb.x;
    float dy = va.y - vb.y;
    float dz = va.z - vb.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}


///全局0向量
extern const Vector3 kZeroVector;
