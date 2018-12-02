#pragma once
#include "code/core/primitive/Vertex.h"
#include "code/core/basic/BaseObject.h"
#include "code/core/Render/Material.h"

class Mesh : public BaseObject
{
public:

    virtual Vertex* GetVerteies() = 0;
    virtual const int* GetIndeies(int* c) = 0;
    inline void SetMat(const Material& mat){ m_mat = mat; }
    inline const Material& GetMat(){ return m_mat; }
    virtual void Start(){}
    virtual void OnEnable(){}
    virtual void OnDisable(){}
private:
    Material m_mat;
};