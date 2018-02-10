//四元素类，以四元素形式保存方位和角位移

#pragma once

class Vector3;
class EulerAngles;

class Quaternion
{
public:
    //公共数据
    float w, x, y, z;
    
    //四元素单位化
    void identity()
    {
        w = 1.0f; x = y = z = 0.0f;
    }

    //构造执行旋转的四元素
    void setToRotateAboutX(float theta);
    void setToRotateAboutY(float theta);
    void setToRotateAboutZ(float theta);
    void setToRotateAboutAxis(const Vector3 &axis, float theta);

    //构造执行物体-惯性旋转的四元素， 方位参数使用欧拉角形式给出
    void setToRotateObjectToInertial(const EulerAngles &orientation);
    void setToRotateInertialToObject(const EulerAngles &orientation);

    //叉乘
    Quaternion operator *(const Quaternion &a) const;

    //
    Quaternion &operator *=(const Quaternion &a);

    //将四元素正则化
    void normalize();

    //提取旋转角和旋转轴
    float getRotateAngle() const;
    Vector3 getRotateAxis() const;
};

//全局单位四元素
extern const Quaternion kQuaternionIdentity;

//四元素点乘
extern float dotProduct(const Quaternion &a, const Quaternion &b);

//球面线性插值
extern Quaternion slerp(const Quaternion &p, const Quaternion &q, float t);

//四元素共轭
extern Quaternion conjugate(const Quaternion &q);

//四元素幂
extern Quaternion pow(const Quaternion &q, float exponent);