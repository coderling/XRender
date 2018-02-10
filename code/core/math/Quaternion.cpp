#include <assert.h>
#include <math.h>

#include "Quaternion.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"

//全局单位四元素
const Quaternion kQuaternionIdentity = {
    1.0f, 0.0f, 0.0f, 0.0f
};

//构造绕指定轴旋转的四元素
void Quaternion::setToRotateAboutX(float theta)
{
    //计算半角
    float thetaOver2 = theta * 0.5f;

    w = cos(thetaOver2);
    x = sin(thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
    //半角
    float thetaOver2 = theta * 0.5f;

    w = cos(thetaOver2);
    x = 0.0f;
    y = sin(thetaOver2);
    z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
    float thetaOver2 = theta * 0.5f;

    w = cos(thetaOver2);
    x = 0.0f;
    y = 0.0f;
    z = sin(thetaOver2);
}

//构造绕任意轴旋转的四元数
void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
    //旋转轴必须是标准化的
    assert(fabs(vectorMag(axis) - 1.0f) < 0.1f);
    
    //半角
    float thetaOver2 = theta * 0.5f;
    float sinThetaOver2 = sin(thetaOver2);

    w = cos(thetaOver2);
    x = axis.x * sinThetaOver2;
    y = axis.y * sinThetaOver2;
    z = axis.z * sinThetaOver2;
}


//构造执行物体-惯性旋转的四元素，参数为欧拉角形式
void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{
    float sp, sb, sh;
    float cp, cb, ch;

    sinCos(&sp, &cp, orientation.pitch * 0.5f);
    sinCos(&sb, &cb, orientation.bank * 0.5f);
    sinCos(&sh, &ch, orientation.heading * 0.5f);

    w = ch * cp * cb + sh * sp * sb;
    x = ch * sp * cb + sh * cp * sb;
    y = -ch * sp * sb + sh * cp * cb;
    z = -sh * sp * cb + ch * cp * sb;
}

//够着执行惯性-物体旋转的四元素，参数为欧拉角形式
void Quaternion::setToRotateInertialToObject(const EulerAngles & orientation)
{
    float sp, sb, sh;
    float cp, cb, ch;
    sinCos(&sp, &cp, orientation.pitch * 0.5f);
    sinCos(&sb, &cb, orientation.bank * 0.5f);
    sinCos(&sh, &ch, orientation.heading * 0.5f);

    w = ch * cp * cb + sh * sp * sb;
    x = -ch * sp * cb - sh * cp * sb;
    y = ch * sp * sb - sh * cb * cp;
    z = sh * sp * cb - ch * cp * sb;
}

Quaternion Quaternion::operator*(const Quaternion &a) const
{
    Quaternion res;

    res.w = w * a.w - x * a.x - y * a.y - z * a.z;
    res.x = w * a.x + x * a.w + z * a.y - y * a.z;
    res.y = w * a.y + y * a.w + x * a.z - z * a.x;
    res.z = w * a.z + z * a.w + y * a.x - x * a.y;

    return res;
}

Quaternion& Quaternion::operator*=(const Quaternion &a)
{
    *this = *this * a;
    return *this;
}

//四元素正则化
void Quaternion::normalize()
{
    //计算四元素的模
    float mag = (float)sqrt(w * w + x * x + y * y + z * z);

    //检测长度，防止除0错误
    if(mag > 0.0f)
    {
        float oneOverMag = 1.0f / mag;
        w *= oneOverMag;
        x *= oneOverMag;
        y *= oneOverMag;
        z *= oneOverMag;
    }
    else
    {
        //error
        assert(false);

        //release 中返回单位四元素
        identity();
    }
}

//返回旋转角
float Quaternion::getRotateAngle() const
{
    //计算半角
    float thetaOver2 = safeAcos(w);
    

    return thetaOver2 * 2.0f;
}


//返回旋转轴
Vector3 Quaternion::getRotateAxis() const
{
    float sinThetaOver2Sq = 1.0f - w * w;

    if(sinThetaOver2Sq <= 0.0f)
    {
        //为单位四元数，或不精确的值，返回有效向量
        return Vector3(1.0f, 0.0f, 0.0f);
    }

    //1/sin(theta/2)
    float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

    return Vector3(
        x * oneOverSinThetaOver2,
        y * oneOverSinThetaOver2,
        z * oneOverSinThetaOver2
    );
}


////////////////////////非成员函数//////////////////////////////////

//点乘
float dotProduct(const Quaternion &a, const Quaternion &b)
{
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

//球面线性插值
Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
    //检查边界参数，返回边界点
    if(t <= 0.0f)
    {
        return q0;
    }

    if(t >= 1.0f)
    {
        return q1;
    }

    //点乘计算cos值
    float cosOmega = dotProduct(q0, q1);

    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;
    if(cosOmega < 0.0f)
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }

    //点乘结果应该小于1，因为是两个单位四元数
    assert(cosOmega < 1.1f);

    float k0, k1;
    if(cosOmega > 0.9999f)
    {
        //非常接近，即线性插值，防止除0
        k0 = 1.0f -t;
        k1 = t;
    }
    else
    {
        float sinOmega = sqrt(1.0f - cosOmega * cosOmega);

        float omega = atan2(sinOmega, cosOmega);

        float oneOverSinOmega = 1.0f/ sinOmega;

        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    //进行插值
    Quaternion res;
    res.x = k0 * q0.x + k1 * q1x;
    res.y = k0 * q0.y + k1 * q1y;
    res.z = k0 * q0.z + k1 * q1z;
    res.w = k0 * q0.w + k1 * q1w;

    return res;
}

//四元素共轭，即与原四元素旋转方向相反的四元素
Quaternion conjugate(const Quaternion &q)
{
    Quaternion res;

    res.w = q.w;

    res.x = -q.x;
    res.y = -q.y;
    res.z = -q.z;

    return res;
}

//四元素幂

Quaternion pow(const Quaternion &q, float exponent)
{
    if(fabs(q.w) > 0.9999f)
    {
        return q;
    }

    //提取半角
    float alpha = acos(q.w);

    float newAlpha = alpha * exponent;

    Quaternion res;
    res.w = cos(newAlpha);
    float mult = sin(newAlpha) / sin(alpha);
    res.x = q.x * mult;
    res.y = q.y * mult;
    res.z = q.z * mult;

    return res;
}