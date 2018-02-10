#include<math.h>

#include "EulerAngles.h"
#include "Quaternion.h"
#include "MathUtil.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"

//全局单位欧拉角常量
//现在还不知道它的确切的构造时机，这取决于其他对象

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

//EulerAngles:cononize()
//将欧拉角限制在限制集里面
void EulerAngles::canonize()
{
    //1.将pitch变换到[-pi,pi]之间
    pitch = wrapPI(pitch);

    //2.将pitch变换到[-pi/2, pi/2]之间
    if(pitch < -kPIOver2)
    {
        pitch = -kPI - pitch;
        heading += kPI;
        bank += kPI;
    }
    else if(pitch > kPIOver2)
    {
        pitch = kPI - pitch;
        heading += kPI;
        bank += kPI;
    }

    //3. 检查万向锁，允许存在一定误差
    if(fabs(pitch) > kPIOver2 - 1e-4)
    {
        //万向锁情况下，将所有轴绕垂直的轴旋转赋给heading
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        bank = wrapPI(heading);
    }

    //4. 将heading转换到限制集
    heading = wrapPI(heading);
}



//EulerAngles:fromInterialToObjectQuaternion()
//从物体-惯性到四元素到欧拉角
void EulerAngles::fromInterialToObjectQuaternion(const Quaternion &q)
{
    //sin(pitch)
    float sp = -2.0f * (q.y * q.z - q.w * q.x);
    
    //检查万向锁，允许一定误差
    if(fabs(sp) > 0.9999f)
    {
        //向正上方或正下方看
        pitch = kPIOver2 * sp;

        //bank 置零，计算heading
        //atan2比atan更稳定
        heading = atan2(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
        bank = 0.0f;
    }
    else
    {
        //计算角度
        pitch = asin(sp);
        heading = atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
        bank = atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
    }
}


//EulerAngles:fromObjectToInterialQuaternion
//从惯性-物体四元数到欧拉角
void EulerAngles::fromObjectToInterialQuaternion(const Quaternion &q)
{
    //sin(pitch)
    float sp = -2.0f * (q.y * q.z + q.w * q.z);

    //检查万向锁
    if(fabs(sp) > 0.9999f)
    {
        //向正上方或正下方看
        pitch = kPIOver2 * sp;

        //blank重置
        heading = atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
        bank = 0.0f;
    }
    else
    {
        //计算角度
        pitch = asin(sp);
        heading = atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
        bank = atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
    }
}

//EulerAngles:fromObjectToWorldMatrix
//从物体-世界坐标系变换矩阵到欧拉角
//假设矩阵是正交的，忽略平移部分
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
    //通过m32计算sin(pitch)
    float sp = -m.m32;

    //检查万向锁
    if(fabs(sp) > 0.9999f)
    {
        //向正上方或正下方看
        pitch = kPIOver2 * sp;

        //bank置零，计算heading
        heading = atan2(-m.m23, m.m11);
        bank = 0.0f;
    }
    else
    {
        //计算角度
        heading = atan2(m.m31, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m12, m.m22);
    }
}

//EulerAngles:fromWorldToObjectMatrix
//从世界-物体坐标变换矩阵到欧拉角
//假设矩阵是正交的，忽略平移部分,惯性嘛
void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
{
    //通过m23计算sin(pitch)
    float sp = -m.m23;

    //检查万向锁
    if(fabs(sp) > 0.9999f)
    {
        //从正上方或正下方看
        pitch = kPIOver2 * sp;

        //bank置零，计算heading
        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //计算角度
        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}

//EulerAngles:fromRotationMatrix
//旋转矩阵构造欧拉角
void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
{
    //计算sin(pitch)
    float sp = -m.m23;

    //检查万向锁
    if(fabs(sp) > 0.99999f)
    {
        //向正上方或正下方看
        pitch = kPIOver2 * sp;
        
        //bank置零，计算heading
        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //计算角度
        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}