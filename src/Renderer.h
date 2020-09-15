#pragma once
#include <stdint.h>
#include <vector>
#include <memory>

#include "Mesh.h"
#include "Matrial.h"
#include "Vertex.h"


namespace XRender
{
    
class Renderer
{
public:
    virtual ~Renderer();
    Renderer();
    void Batch();
    void SetMatrix(const Matrix* matrix);
    const uint32_t& GetVbo() const;
public:
    bool active;
    bool geometryDirty;
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Matrial> mat;
private:
    const Matrix* matrix;
    uint32_t vbo_id;
};

}