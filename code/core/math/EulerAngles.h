#pragma once

/*
欧拉角，heading-pitch-bank
*/

class Quaternion;
class Matrix4x3;
class RotationMatrix;

//begin EulerAngles

class EulerAngles
{
public:
    //just save the Angle directly
    float heading;
    float pitch;
    float bank;

    //default constructor
    EulerAngles() {}

    //by free pramas
    EulerAngles(float h, float p, float b) :
    heading(h), pitch(p), bank(b) {}

    //zero
    void identity() { pitch = bank = heading = 0.0f; }

    //转换为限制欧拉角
    void canonize();

    //从四元素转换到欧拉角
    //假设输入四元素物体-惯性或惯性-物体四元素
    void fromObjectToInterialQuaternion(const Quaternion &q);
    void fromInterialToObjectQuaternion(const Quaternion &q);

    //从矩阵转换到欧拉角
    //输入矩阵假设为物体-世界或者世界-物体的变换矩阵
    //平移部分被省略，并且假设矩阵是正交的
    void fromObjectToWorldMatrix(const Matrix4x3 &m);
    void fromWorldToObjectMatrix(const Matrix4x3 &m);
    
    //从旋转矩阵转换到欧拉角
    void fromRotationMatrix(const RotationMatrix &m);
};

//全局的单位欧拉角
extern const EulerAngles kEulerAnglesIdentity;