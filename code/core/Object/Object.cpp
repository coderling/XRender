#include "Object.h"

Matrix4x3 Object::ModelMatrix()
{
    m_modelMat.setupLocalToParent(m_position, EulerAngles(m_rotation.y, m_rotation.x, m_rotation.z));
    return m_modelMat;
}