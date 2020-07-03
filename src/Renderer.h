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
    void UpdateMatrix(const Matrix& matrix);
public:
    bool active;
    bool geometryDirty;
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Matrial> mat;
    
private:
    Matrix model_matrix;
    uint32_t vbo_id;
};

}