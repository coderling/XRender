#include <stdint.h>
#include <algorithm>
#include <cassert>
#include <any>

#include "Graphics.h"
#include "GraphicsGlobalData.h"
#include "./math/Math.h"

XRender::Graphics::~Graphics(){}

uint32_t XRender::Graphics::CreateVBO(const uint32_t &count)
{
    uint32_t vbo_id = ++vbo_id_source;
    VertexBuffer buffer;
    Vertex* vbo = new Vertex[count];
    buffer.vertex_buffer = vbo;
    buffer.vertex_count = count;
    buffer.index_buffer = nullptr;
    buffer.index_count = 0;
    return vbo_id;
}

void XRender::Graphics::CreateVIO(const uint32_t& buffer_id, const uint32_t& count)
{
    assert(buffers.count(buffer_id) == 1);
    uint32_t* vio = new uint32_t[count];
    if(buffers[buffer_id].index_buffer != nullptr)
    {
        delete [] buffers[buffer_id].index_buffer;
    }
    buffers[buffer_id].index_buffer = vio;
    buffers[buffer_id].index_count = count;
}

void XRender::Graphics::LoadVertexBuffer(const uint32_t &buffer_id, const Vertex *vertex_buffer)
{
    assert(buffers.count(buffer_id) == 1);
    Vertex* vbo = buffers[buffer_id].vertex_buffer;
    for(uint32_t index = 0; index < buffers[buffer_id].vertex_count; ++index)
    {
        vbo[index] = vertex_buffer[index]; 
    }
}

void XRender::Graphics::LoadIndexBuffer(const uint32_t &buffer_id, const uint32_t *index_buffer)
{
    assert(buffers.count(buffer_id) == 1 && buffers[buffer_id].index_buffer != nullptr);
    uint32_t* vio = buffers[buffer_id].index_buffer;
    for(uint32_t index = 0; index < buffers[buffer_id].vertex_count; ++index)
    {
        vio[index] = index_buffer[index]; 
    }
}

void XRender::Graphics::BindShader(const uint32_t& buffer_id, Shader *shader)
{
    assert(buffers.count(buffer_id) == 1);
    shader_map.emplace(buffer_id, shader);
}

void XRender::Graphics::LoadModelMatrix(const uint32_t& buffer_id, const Matrix& matrix)
{
    assert(buffers.count(buffer_id) == 1);
    model_matries.insert_or_assign(buffer_id, matrix);
}

void XRender::Graphics::ReleaseVBOANDVIO(const uint32_t& buffer_id)
{
    auto buffer_iter = buffers.find(buffer_id);
    if(buffer_iter != buffers.end())
    {
        auto buffer = buffer_iter->second;
        buffers.erase(buffer_id);
        ReleaseVertexBuffer(buffer);
    }
    if(shader_map.count(buffer_id) == 1)
    {
        shader_map.erase(buffer_id);
    }
}

void XRender::Graphics::ReleaseVertexBuffer(VertexBuffer& buffer)
{
    if(buffer.vertex_buffer != nullptr)
    {
        delete [] buffer.vertex_buffer;
        buffer.vertex_buffer = nullptr;
        buffer.vertex_count = 0;
    }

    if(buffer.index_buffer != nullptr)
    {
        delete [] buffer.index_buffer;
        buffer.index_buffer = nullptr;
        buffer.index_count = 0;
    }
}

void XRender::Graphics::Dispose()
{
    for(auto& pv:buffers)
    {
        ReleaseVertexBuffer(pv.second);
    }
    buffers.clear();
    shader_map.clear();
}

bool XRender::Graphics::DepthTest(const uint32_t &x, const uint32_t &y, const float &depth)
{
    return true;
}

void XRender::Graphics::InitRenderContext(const uint32_t& width, const uint32_t& height)
{
    render_context.Init(width, height);
}

uint32_t XRender::Graphics::GetContextWidth() const
{
    return render_context.GetWidth();
}

uint32_t XRender::Graphics::GetContextHeight() const
{
    return render_context.GetHeight();
}

const XRender::RenderContext& XRender::Graphics::GetRenderContext() const
{
    return render_context;
}

void XRender::Graphics::Execute()
{
    for(const auto& kv : shader_map)
    {
        current_execute_vbo_id = kv.first;
        SetupGlobalData();
        ExecuteVertexShader();
        Rasterizer();
        ExecuteFragmentShader();
    }
    current_execute_vbo_id = 0;
}

void XRender::Graphics::SetupGlobalData()
{
    GraphicsGlobalData::matrix_m = model_matries[current_execute_vbo_id];
    GraphicsGlobalData::matrix_mv = GraphicsGlobalData::matrix_p * GraphicsGlobalData::matrix_m;
    GraphicsGlobalData::matrix_mvp = GraphicsGlobalData::matrix_p * GraphicsGlobalData::matrix_mv;
}

void XRender::Graphics::BindVertexInput(const uint32_t& index)
{
    Shader* shader = shader_map[current_execute_vbo_id];
    bind_vertex_input.data.clear();
    for(uint32_t st = static_cast<uint32_t>(SEMANTIC::POSITION); st < static_cast<uint32_t>(SEMANTIC::MAX); ++st)
    {
        auto semantic = static_cast<SEMANTIC>(st);
        if(shader->HasVertexInputSemantic(semantic))
        {
            FillSemanticToVertexInput(index, semantic);
        }
    }
}

void XRender::Graphics::FillSemanticToVertexInput(const uint32_t& index, const SEMANTIC& st)
{
    Vertex* vertex_buffer = buffers[current_execute_vbo_id].vertex_buffer;
    const Vertex& vertex = vertex_buffer[index];
    switch (st) 
    {
        case SEMANTIC::POSITION: 
            FILL_SHADER_STRUCT(bind_vertex_input, st, vertex.pos);
        break;
        case SEMANTIC::COLOR:
            FILL_SHADER_STRUCT(bind_vertex_input, st, vertex.color);
        break;
        case SEMANTIC::NORMAL:
            FILL_SHADER_STRUCT(bind_vertex_input, st, vertex.normal);
        break;
        case SEMANTIC::UV0:
            FILL_SHADER_STRUCT(bind_vertex_input, st, vertex.uv);
        break;
        case SEMANTIC::UV1:
            FILL_SHADER_STRUCT(bind_vertex_input, st, vertex.uv2);
        break;
        default:
        break;
    }
}

void XRender::Graphics::ExecuteVertexShader()
{
    cached_vertex_out.clear();
    VertexBuffer buffer = buffers[current_execute_vbo_id];
    Shader* shader = shader_map[current_execute_vbo_id];
    assert(shader->HasVertexInputSemantic(SEMANTIC::POSITION));
    for(uint32_t index = 0; index < buffer.vertex_count; ++index)
    {
        BindVertexInput(index);
        VertexOutput out = shader->Vertex(bind_vertex_input);
        cached_vertex_out.emplace_back(out);
    }
}

void XRender::Graphics::Rasterizer()
{
    cached_frament_in.clear();
    VertexBuffer buffer = buffers[current_execute_vbo_id];
    uint32_t triangle_count = buffer.index_count / 3;
    for(uint32_t index = 0; index < triangle_count; ++index)
    {
        RasterizerTriangle(index);
    }
    cached_vertex_out.clear();
}

void XRender::Graphics::RasterizerTriangle(const uint32_t& index)
{
    Vec4f* triangle = cached_triangle.points;
    for(uint32_t sub_index = 0; sub_index < 3; ++sub_index)
    {
        cached_triangle.vertex_outs[sub_index] = &cached_vertex_out[index + sub_index];
		Vec4f v;
		auto the_struct = *cached_triangle.vertex_outs[sub_index];
    {\
    auto it = the_struct.data.find(SEMANTIC::SV_POSITION);\
    if(it != the_struct.data.end()) v = std::any_cast<Vec4f>(it->second);\
	}
		//GET_DATA_BY_SEMATIC(v, (*(cached_triangle.vertex_outs[sub_index])), SEMANTIC::SV_POSITION, Vec4f);
        v[0] /= v[3]; v[1] /= v[3]; v[2] /= v[3];
        FILL_SHADER_STRUCT((*(cached_triangle.vertex_outs[sub_index])), SEMANTIC::SV_POSITION, v);
        triangle[sub_index] = v;
    }

    auto [lb, rt] = Math::TriangleBoundingBox(embed<3>(triangle[0]), embed<3>(triangle[1]), embed<3>(triangle[2]));
    lb.x = std::clamp(lb.x, 0, (int)render_context.GetWidth());
    lb.y = std::clamp(lb.y, 0, (int)render_context.GetHeight());
    rt.x = std::clamp(rt.x, 0, (int)render_context.GetWidth());
    rt.y = std::clamp(rt.y, 0, (int)render_context.GetHeight());

    Vec2f center_point;
    Vec2f p1 = embed<2>(triangle[0]);
    Vec2f p2 = embed<2>(triangle[1]);
    Vec2f p3 = embed<2>(triangle[2]);
    for(uint32_t x = lb.x; x < rt.x; ++x)
    {
        for(uint32_t y = lb.y; y < rt.y; ++y)
        {
            center_point.x = x + 0.5;
            center_point.y = y + 0.5;
            auto[alpha, beta, gamma] = Math::TriangleBarycentric(p1, p2, p3, center_point);
            if(alpha < 0 || beta < 0 || gamma < 0) continue;
            PropertyBarycentricInterpolation(Vec2i(x, y), Vec3f(alpha, beta, gamma));
        }
    }
}

void XRender::Graphics::PropertyBarycentricInterpolation(const Vec2i& point, const Vec3f& barycentric)
{
    Vec4f* triangle = cached_triangle.points;
    Shader* shader = shader_map[current_execute_vbo_id];
    float viewZ = 1.f / (barycentric.x / triangle[0][3] + barycentric.y / triangle[1][3] + barycentric.z / triangle[2][3]);
    float A = barycentric.x / (triangle[0].w * viewZ);
    float B = barycentric.y / (triangle[1].w * viewZ);
    float G = barycentric.z / (triangle[2].w * viewZ);
    float depth = Math::BarycentricInterpolation<float>(triangle[0].z, triangle[1].z, triangle[2].z, Vec3f(A, B, G));
    if(!DepthTest(point.x, point.y, depth)) return;

    VertexOutput framgent_in;
    framgent_in.x = point.x; framgent_in.y = point.y;
    Vec4f shade_pos = Math::BarycentricInterpolation<Vec4f>(triangle[0], triangle[1], triangle[2], barycentric);
    FILL_SHADER_STRUCT(framgent_in, SEMANTIC::SV_POSITION, shade_pos);
    for(auto interpolation : shader->propertory_interpolation_funcs)
    {
        if(interpolation.first == SEMANTIC::SV_POSITION) continue;
        interpolation.second(framgent_in, cached_triangle.vertex_outs, interpolation.first, barycentric);
    }

    cached_frament_in.emplace_back(framgent_in);
}

void XRender::Graphics::ExecuteFragmentShader()
{
    Shader* shader = shader_map[current_execute_vbo_id];
    Color color;
    for(auto framgent_in : cached_frament_in)
    {
        shader->Fragment(framgent_in, color);
        AfterFramgent(framgent_in.x, framgent_in.y, color);
    }
    cached_frament_in.clear();
}

void XRender::Graphics::AfterFramgent(const uint32_t& x, const uint32_t& y, const Color& color)
{
    render_context.SetPixel(x, y, color);
}

XRender::Graphics& XRender::Graphics::VirtualGraphic()
{
	static XRender::Graphics virtual_graphic;
	return virtual_graphic;
}