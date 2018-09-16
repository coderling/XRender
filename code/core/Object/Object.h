#pragma once
#include "code/includes.h"
//3d 对象

class Object
{
public:
    Vector3 m_position;
    Vector3 m_scale;
    Vector3 m_rotation;

public:
    Object()
    {
        m_position.zero();
        m_scale.x = m_scale.y = m_scale.z = 1;
        m_rotation.zero();
        m_modelMat.identity();
    }

    Matrix4x3 ModelMatrix();

protected:
    Matrix4x3 m_modelMat;
};