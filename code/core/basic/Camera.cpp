#include "Camera.h"

void Camera::Init(const Uint32& screenW, const Uint32& screenH,
                const Vector3& pos, const Vector3& up, const Vector3& lookPos)
{
    m_screenW = screenW;
    m_screenH = screenH;
    m_pos = pos;
    m_cMat.identity();
    m_pMat.identity();
    LookAtMatrix(m_pos, lookPos, up, m_up, m_view, m_right, m_cMat);
    CaculateProjectMatrix();
    m_vpMat = m_cMat * m_pMat;
}

void Camera::CaculateProjectMatrix()
{
    // 投影矩阵，cvv z[0, 1]
    m_ratio = m_screenW * 1.0f / m_screenH;
    //计算视锥体投影平面的宽
    float rfov = m_fov * kPI / 360.0f;// 180.f / 2
    float vh = 2 * m_near * tanf(rfov);
    float vw = vh * m_ratio;

    //支持特殊投影平面x、y方向都是居中的情况
    float a = m_far / (m_far - m_near);
    float b = m_far * m_near / (m_near - m_far);

    m_pMat.m11 = 2 * m_near / vw;
    m_pMat.m12 = 0.0f;
    m_pMat.m13 = 0.0f;

    m_pMat.m21 = 0.0f;
    m_pMat.m22 = 2 * m_near / vh;
    m_pMat.m23 = 0.0f;
    
    m_pMat.m31 = 0.0f;
    m_pMat.m32 = 0.0f;
    m_pMat.m33 = a;

    m_pMat.tx = 0.0f;
    m_pMat.ty = 0.0f;
    m_pMat.tz = b;
}

Vector3 Camera::DoVertexTranslate(const Vector3& vec)
{
    return vec * m_vpMat;
}

void Camera::Update()
{

}

void Camera::LookAtMatrix(const Vector3& pos, const Vector3& lookPos, const Vector3& up, Vector3& rup, Vector3& view, Vector3& right, Matrix4x3& vmat)

{
    //计算右向量，通过up view right三者是互相垂直的关系计算。
    view = lookPos - pos;
    rup = up;
    rup.normalize();
    right = crossProduct(rup, view);
    right.normalize();
    //修正view
    view = crossProduct(right, up);
    view.normalize();

    //求摄像机矩阵，思路：使得right, up, view, 与世界坐标系重叠。平移pos的负向量，再执行旋转。
    //那么有right x [m11, m12, m13] = [1, 0, 0], up x [m21, m22, m23] = [0, 1, 0]
    //view x [m31, m32, m33] = [0, 0, 1]，这里right, up, view组成的矩阵是标准正交基，
    //所以旋转矩阵为它的逆，也就是它的转置

    //旋转矩阵
    RotationMatrix rmat;
    rmat.identity();
    rmat.m11 = right.x, rmat.m21 = right.y, rmat.m23 = right.z;
    rmat.m12 = up.x, rmat.m22 = up.y; rmat.m32 = up.z;
    rmat.m13 = view.x, rmat.m23 = view.y; rmat.m33 = view.z;
    vmat.setupParentToLocal(pos, rmat);
}