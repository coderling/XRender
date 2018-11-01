#include "Object.h"
#include "code/core/math/EulerAngles.h"

Object::Object()
{
    m_position.zero();
    m_scale.x = m_scale.y = m_scale.z = 1;
    m_rotation.zero();
    m_modelMat.identity();
    m_pMesh = nullptr;
}

Object::~Object()
{
    if(m_pMesh != nullptr)
    {
        delete m_pMesh;
        m_pMesh = nullptr;
    }
}

Matrix4x3 Object::ModelMatrix()
{
    m_modelMat.setupLocalToParent(m_position, EulerAngles(m_rotation.y, m_rotation.x, m_rotation.z));
    return m_modelMat;
}

void Object::AttachMesh(Mesh* mesh)
{
    m_pMesh = mesh;
}

Mesh* Object::GetMesh()
{
    return m_pMesh;
}

void Object::AttachBehavior(Behavior& behavior)
{
    behavior.m_object = this;
    m_behaviors.push_back(behavior);
}

void Object::RemoveBehavior(Behavior& behavior)
{
    for(auto it = m_behaviors.begin(); it != m_behaviors.end(); it++)
    {  
        if(*it == behavior)
        {
            m_behaviors.erase(it);
            break;
        }
    }
}

void Object::StartBehaviors()
{
    for(auto be : m_behaviors)
    {
        be.Start();
    }
}

void Object::UpdateBehaviors()
{
    for(auto be : m_behaviors)
    {
        be.Update();
    }
}