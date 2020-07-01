#pragma once
#include <stdint.h>
#include <map>
#include <vector>
#include <functional>

#include "Semantic.h"
#include "Vertex.h"
#include "Shader.h"
#include "geometry.h"
#include "RenderContext.h"

namespace XRender
{

class Graphics final
{
private:
    struct VertexBuffer
    {
    public:
        uint32_t id;
        uint32_t vertex_count;
        uint32_t index_count;
        Matrix world_matrix;
        Vertex* vertex_buffer;
        uint32_t* index_buffer;
    };

    struct Triangle
    {
    public:
        VertexOutput* vertex_outs[3];
        Vec4f points[3];
    };
public:
	static Graphics& VirtualGraphic();
public:
    ~Graphics();
    uint32_t CreateVBO(const uint32_t& count);
    void LoadVertexBuffer(const uint32_t& buffer_id, const Vertex* source_data);
    void LoadVertex(const uint32_t& buffer_id, const uint32_t& index, const Vertex& vertex);
    void CreateVIO(const uint32_t& buffer_id, const uint32_t& count);
    void LoadIndexBuffer(const uint32_t& buffer_id, const uint32_t* source_data);
    void BindShader(const uint32_t& buffer_id, Shader* shader);
    void LoadModelMatrix(const uint32_t& buffer_id, const Matrix& matrix);
    void ReleaseVBOANDVIO(const uint32_t& buffer_id);
    void Dispose();
    void Execute();
    void InitRenderContext(const uint32_t& width, const uint32_t& height);
    uint32_t GetContextWidth() const;
    uint32_t GetContextHeight() const;
    const RenderContext& GetRenderContext() const;
private:
    void SetupGlobalData();
    void ExecuteVertexShader();
    void ExecuteFragmentShader();
    void Rasterizer();
    void RasterizerTriangle(const uint32_t& index);
    void PropertyBarycentricInterpolation(const Vec2i& point, const Vec3f& barycentric);
    bool DepthTest(const uint32_t& x, const uint32_t& y, const float& depth);
    void AfterFramgent(const uint32_t& x, const uint32_t& y, const Color& color);
    void BindVertexInput(const uint32_t& index);
    void FillSemanticToVertexInput(const uint32_t& index, const SEMANTIC& st);
    void ReleaseVertexBuffer(VertexBuffer& buffer);
    
    VertexInput bind_vertex_input;
    std::vector<VertexOutput> cached_vertex_out;
    Triangle cached_triangle;
    std::vector<VertexOutput> cached_frament_in;
    uint32_t current_execute_vbo_id;
    
    std::map<uint32_t, VertexBuffer> buffers;
    std::map<uint32_t, Shader*> shader_map; 
    std::map<uint32_t, Matrix> model_matries; 
    uint32_t vbo_id_source;
    RenderContext render_context;
};
}