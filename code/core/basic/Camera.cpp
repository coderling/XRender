#include "Camera.h"

Camera::Camera(const Vector3& pos, const Vector3& up, const Vector3& lookPos)
{
    m_pos = pos;
    m_up = up;
    LookAtMatrix(m_pos, lookPos, m_up, m_view, m_right, m_cMat);
}

void LookAtMatrix(const Vector3& pos, const Vector3& lookPos, Vector3& up, Vector3& view, Vector3& right, Matrix4x3& vmat)

{
    //计算右向量，通过up view right三者是互相垂直的关系计算。
    view = lookPos - pos;
    up.normalize();
    right = crossProduct(up, view);
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
    rmat.m11 = right.x, rmat.m21 = right.y, rmat.m23 = right.z;
    rmat.m12 = up.x, rmat.m22 = up.y; rmat.m32 = up.z;
    rmat.m13 = view.x, rmat.m23 = view.y; rmat.m33 = view.z;
    vmat.setupParentToLocal(pos, rmat);
}