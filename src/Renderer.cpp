#include <cstdlib>
#include <stdint.h>
#include <vector>

#include "Renderer.h"
#include "Graphics.h"
#include "geometry.h"

XRender::Renderer::~Renderer(){}

XRender::Renderer::Renderer(): vbo_id(0) {}

void XRender::Renderer::Batch() 
{
    auto virtual_graphics = Graphics::VirtualGraphic();
    if (vbo_id > 0)
    {
        virtual_graphics.ReleaseVBOANDVIO(vbo_id);
        vbo_id = 0;
    }

    uint32_t vertex_count = mesh->GetVertexCount(); 
    if(vertex_count == 0) return;
    
    vbo_id = virtual_graphics.CreateVBO(vertex_count); 
	Vertex* verteies = new Vertex[vertex_count];
    for(uint32_t index = 0; index < vertex_count; ++index)
    {
        mesh->GetVertexByIndex(verteies[index], index);
    }
    virtual_graphics.LoadVertexBuffer(vbo_id, &(verteies[0]));
	delete[] verteies;

    const std::vector<uint32_t>& indeies = mesh->GetIndeies();
    virtual_graphics.CreateVIO(vbo_id, indeies.size()); 
    virtual_graphics.LoadIndexBuffer(vbo_id, &(indeies[0]));

    virtual_graphics.LoadModelMatrix(vbo_id, model_matrix);
    virtual_graphics.BindShader(vbo_id, mat->shader.get());
}

XRender::Vertex* XRender::Renderer::GetVerteies()
{
    return verteies;
}

void XRender::Renderer::UpdateMatrix(const Matrix& matrix)
{
    auto virtual_graphics = Graphics::VirtualGraphic();
    virtual_graphics.LoadModelMatrix(vbo_id, model_matrix);
}

