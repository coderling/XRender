#include <cstdlib>
#include <stdint.h>
#include <vector>

#include "Renderer.h"
#include "Graphics.h"
#include "./resources/Resources.h"

XRender::Renderer::~Renderer()
{
    XRender::Res::Resources::UnLoad<Mesh>(std::move(mesh));
    matrix = nullptr;
}

XRender::Renderer::Renderer(): active(true), geometryDirty(true), vbo_id(0)
{
}

void XRender::Renderer::Batch() 
{
    auto& virtual_graphics = Graphics::VirtualGraphic();
    if (vbo_id > 0)
    {
        virtual_graphics.ReleaseVBOANDVIO(vbo_id);
        vbo_id = 0;
    }

    uint32_t vertex_count = mesh->GetVertexCount(); 
    if(vertex_count == 0) return;
    
    vbo_id = virtual_graphics.CreateVBO(vertex_count); 
    for(uint32_t index = 0; index < vertex_count; ++index)
    {
        Vertex vertex;
        mesh->GetVertexByIndex(vertex, index);
        virtual_graphics.LoadVertex(vbo_id, index, vertex);
    }

    const std::vector<uint32_t>& indeies = mesh->GetIndeies();
    virtual_graphics.CreateVIO(vbo_id, indeies.size()); 
    virtual_graphics.LoadIndexBuffer(vbo_id, &(indeies[0]));
    virtual_graphics.LoadModelMatrix(vbo_id, this->matrix);
    virtual_graphics.BindShader(vbo_id, mat->shader.get());
}

void XRender::Renderer::SetMatrix(const Matrix* matrix)
{
    this->matrix = matrix;
}

const uint32_t& XRender::Renderer::GetVbo() const
{
    return vbo_id;
}