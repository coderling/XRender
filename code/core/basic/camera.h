#pragma once
//三维世界的摄像机
#include <SDL.h>
#include "../math/Vector3.h"
#include "../math/MathUtil.h"
#include "../math/Matrix4x3.h"
#include "../math/RotationMatrix.h"

class Camera
{
public:
    Camera(){}
    ~Camera(){}

    inline Vector3 GetPosition(){ return m_pos; }
    inline Vector3 GetUp(){ return m_up; }
    inline Vector3 GetView() { return m_view; }
    inline Vector3 GetRight() { return m_right; }
    inline Matrix4x3 GetCameraMatrix(){ return m_cMat; }
    inline Matrix4x3 GetProjectMatrix(){ return m_pMat; }
    inline Matrix4x3 GetVPMatrix(){ return m_vpMat; }
    void Init(const Uint32& screenW, const Uint32& screenH,
            const Vector3& pos, const Vector3& up, const Vector3& lookPos);
    void Update();

    //执行变换，得到最后的屏幕坐标
    Vector3 DoVertexTranslate(const Vector3& vec);
protected:
    void CaculateProjectMatrix();
private:
    Uint32 m_screenW;
    Uint32 m_screenH;
    Vector3 m_pos;
    Vector3 m_up;
    Vector3 m_view;
    Vector3 m_right;

    //可视距离
    float m_far = 100;
    float m_near = 0.3;

    //水平视野
    float m_fov = 60;

    //宽高比
    float m_ratio;

    //计算后的摄像机矩阵
    Matrix4x3 m_cMat;

    //计算后的透视投影矩阵
    Matrix4x3 m_pMat;

    //计算后的VP矩阵
    Matrix4x3 m_vpMat;



    void LookAtMatrix(const Vector3& pos, const Vector3& lookPos, const Vector3& up, 
                            Vector3& rup, Vector3& view, Vector3& right, Matrix4x3& vmat);
};