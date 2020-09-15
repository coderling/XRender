#pragma once
#include <stdint.h>
#include <map>
#include <vector>
#include <functional>
#include <unordered_set>

#include "Semantic.h"
#include "Vertex.h"
#include "Shader.h"
#include "geometry.h"
#include "RenderContext.h"
#include "NoCopyable.h"
#include "Lighting.h"
#include "GraphicsEnum.h"
#include "RenderTexture.h"
#include "RenderDevice.h"

namespace XRender
{

class Graphics final : NoCopyable
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
    void BeginFrame();
    void Execute();
    void EndFrame();
    void SetupGraphics(const uint32_t& w, const uint32_t& h, const std::string& name);
    uint32_t GetContextWidth() const;
    uint32_t GetContextHeight() const;
    RenderContext* GetRenderContext();
    void AddLight(const Lighting::LightData* light);
    void RemoveLight(const Lighting::LightData* light);
    void ActiveRender(const uint32_t& vbo_id);
    void SetClearFlag(const int& flag);
    void Present();
private:
    void SetupGlobalData();
    void SetupObjectData();
    void ExecuteVertexShader();
    void PerspectiveDivideAndViewPort(VertexOutput& out);
    void ExecuteFragmentShader();
    void Rasterizer();
    void RasterizerTriangle();
    void DrawTriangle(const uint32_t& index);
    void PropertyBarycentricInterpolation(const Vec2i& point, const Vec3f& barycentric);
    bool DepthTest(const uint32_t& x, const uint32_t& y, const float& depth);
    void ApplyFragment(const uint32_t& x, const uint32_t& y, const Color& color, const float& depth);
    void BindVertexInput(const uint32_t& index);
    void FillSemanticToVertexInput(const uint32_t& index, const SEMANTIC& st);
    void ReleaseVertexBuffer(VertexBuffer& buffer);
    bool IsBackFace(const Vec2f& p1, const Vec2f& p2, const Vec2f& p3) const; 

    VertexInput bind_vertex_input;
    VertexOutput fragment_input;
    std::vector<VertexOutput> cached_vertex_out;
    VertexOutput* cached_triangle[3];
    Vec4f cached_triangle_points[3];
    uint32_t current_execute_vbo_id;
    
    std::unordered_set<uint32_t> active_buffers;
    std::map<uint32_t, VertexBuffer> buffers;
    std::map<uint32_t, Shader*> shader_map; 
    std::map<uint32_t, Matrix> model_matries; 
    uint32_t vbo_id_source;
    RenderContext render_context;
    GraphicsEnum::EDepthTestMethod depth_test_method = GraphicsEnum::EDepthTestMethod::Less;

    std::unordered_set<const Lighting::LightData*> lights;
    const Lighting::LightData* shadow_light = nullptr;
    int clear_flag = GraphicsEnum::EClearFlag::Clear_Depth | GraphicsEnum::EClearFlag::Clear_Color;
};
}