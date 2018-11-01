#pragma once

#include "code/core/basic/BaseObject.h"
#include "code/core/math/Vector3.h"
#include "code/core/math/Matrix4x3.h"
#include "code/core/primitive/Vertex.h"
#include "code/core/basic/Mesh.h"
#include "Behavior.h"
#include <vector>
//3d 对象

class Object : public BaseObject
{
    friend class XApp;
public:
    Vector3 m_position;
    Vector3 m_scale;
    Vector3 m_rotation;

public:
    Object();

    virtual ~Object() noexcept;

    Matrix4x3 ModelMatrix();

    void AttachBehavior(Behavior& behavior);
    void RemoveBehavior(Behavior& behavior);
    void AttachMesh(Mesh* mesh);
    Mesh* GetMesh();

    virtual void Start(){}

    virtual void OnEnable(){}

    virtual void OnDisable(){}
protected:
    std::vector<Behavior> m_behaviors;    
    Matrix4x3 m_modelMat;
private:
    void StartBehaviors();
    void UpdateBehaviors();
    Mesh* m_pMesh;
    
};