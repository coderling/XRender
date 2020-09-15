#include <stdint.h>
#include <algorithm>
#include <cassert>
#include <any>
#include <iostream>

#include "Graphics.h"
#include "GraphicsGlobalData.h"
#include "CVVClip.hpp"
#include "./math/Math.h"
#include "platform/common/Platform.h"

XRender::Graphics::~Graphics(){}

uint32_t XRender::Graphics::CreateVBO(const uint32_t &count)
{
    VertexBuffer buffer;
    buffer.id = ++vbo_id_source;
    Vertex* vbo = new Vertex[count];
    buffer.vertex_buffer = vbo;
    buffer.vertex_count = count;
    buffer.index_buffer = nullptr;
    buffer.index_count = 0;
    buffers.emplace(buffer.id, buffer);
    return buffer.id;
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

void XRender::Graphics::LoadVertex(const uint32_t& buffer_id, const uint32_t& index, const Vertex& vertex)
{
    assert(buffers.count(buffer_id) && index < buffers[buffer_id].vertex_count);
    buffers[buffer_id].vertex_buffer[index] = vertex;
}

void XRender::Graphics::LoadIndexBuffer(const uint32_t &buffer_id, const uint32_t *index_buffer)
{
    assert(buffers.count(buffer_id) == 1 && buffers[buffer_id].index_buffer != nullptr);
    uint32_t* vio = buffers[buffer_id].index_buffer;
    for(uint32_t index = 0; index < buffers[buffer_id].index_count; ++index)
    {
        vio[index] = index_buffer[index]; 
    }
}

void XRender::Graphics::BindShader(const uint32_t& buffer_id, Shader *shader)
{
    assert(buffers.count(buffer_id) == 1);
    shader_map.emplace(buffer_id, shader);
}

void XRender::Graphics::LoadModelMatrix(const uint32_t& buffer_id, const Matrix* matrix)
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
    const auto& cur_depth = render_context.ActivedRenderTexture()->DepthOf(x, y);
    switch (depth_test_method) 
    {
        default:
        {
            if(depth < cur_depth)
            {
                return true;
            }
        }
        break;;
    }
    return false;
}

void XRender::Graphics::SetupGraphics(const uint32_t& w, const uint32_t& h, const std::string& name)
{
    RenderDevice::Device()->Setup(name);
    RenderDevice::Device()->Init(w, h);
}

uint32_t XRender::Graphics::GetContextWidth() const
{
    return render_context.GetWidth();
}

uint32_t XRender::Graphics::GetContextHeight() const
{
    return render_context.GetHeight();
}

XRender::RenderContext* XRender::Graphics::GetRenderContext()
{
    return &render_context;
}

void XRender::Graphics::AddLight(const Lighting::LightData* light)
{
    if(lights.count(light) != 0)
    {
        return;
    }

    lights.emplace(light);
}

void XRender::Graphics::RemoveLight(const Lighting::LightData* light)
{
    const auto iter = lights.find(light);
    if(iter != lights.end())
    {
        lights.erase(light);
    }
}


void XRender::Graphics::SetClearFlag(const int& flag)
{
    clear_flag = flag;
}

void XRender::Graphics::BeginFrame()
{
    SetupGlobalData();
}

void XRender::Graphics::Execute()
{
    if((clear_flag & GraphicsEnum::EClearFlag::Clear_Color) != GraphicsEnum::EClearFlag::Clear_None)
        render_context.ClearFrameBuffer();

    if((clear_flag & GraphicsEnum::EClearFlag::Clear_Depth) != GraphicsEnum::EClearFlag::Clear_None)
        render_context.ClearDepthBuffer();

    for(const auto& vbo_id : active_buffers)
    {
        current_execute_vbo_id = vbo_id;
        SetupObjectData();
        ExecuteVertexShader();
        Rasterizer();
    }
}

void XRender::Graphics::EndFrame()
{
    current_execute_vbo_id = 0;
    active_buffers.clear();
}

void XRender::Graphics::SetupGlobalData()
{
    uint32_t index = 0;
    for(const Lighting::LightData* light : lights)
    {
        if(index >= Lighting::max_light_num) break;

        GraphicsGlobalData::lights[index] = light;
        ++index;
    }

    GraphicsGlobalData::light_count = index;
}

void XRender::Graphics::SetupObjectData()
{
    GraphicsGlobalData::matrix_m = *(model_matries[current_execute_vbo_id]);
    GraphicsGlobalData::matrix_mv = GraphicsGlobalData::matrix_v * GraphicsGlobalData::matrix_m;
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
            FILL_SHADER_STRUCT(bind_vertex_input, st, embed<4>(vertex.pos));
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

void XRender::Graphics::PerspectiveDivideAndViewPort(VertexOutput& out)
{
		Vec4f v;
		GET_DATA_BY_SEMATIC(v, out, SEMANTIC::SV_POSITION);
        float w = v.w;
        v.x /= w; v.y /= w; v.z /= w; v.w = 1;
        auto screen_pos = GraphicsGlobalData::matrix_viewport * v;
        out.screen.x = screen_pos.x;
        out.screen.y = screen_pos.y;
        /// v.z [-1, 1] => [0, 1]
        out.viewDepth = v.z * 0.5f + 0.5f;
        out.viewZ = w;
        v.w = w;
        FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, v);
}

bool XRender::Graphics::IsBackFace(const Vec2f& p1, const Vec2f& p2, const Vec2f& p3) const
{
    static Vec2f p3p1;
    static Vec2f p2p1;

    p3p1.x = p3.x - p1.x;
    p3p1.y = p3.y - p1.y;
    p2p1.x = p2.x - p1.x;
    p2p1.y = p2.y - p1.y;
    float signed_value_old = p3p1.x * p2p1.y - p2p1.x * p3p1.y;
    return signed_value_old > 0;
}

void XRender::Graphics::Rasterizer()
{
    VertexBuffer buffer = buffers[current_execute_vbo_id];
    uint32_t triangle_count = buffer.index_count / 3;
    for(uint32_t index = 0; index < triangle_count; ++index)
    {
        DrawTriangle(index);
    }
    cached_vertex_out.clear();
}

void XRender::Graphics::DrawTriangle(const uint32_t& index)
{
    VertexBuffer buffer = buffers[current_execute_vbo_id];
    for(uint32_t sub_index = 0; sub_index < 3; ++sub_index)
    {
		uint32_t t_index = buffer.index_buffer[index * 3 + sub_index];
        cached_triangle[sub_index] = &cached_vertex_out[t_index];
        GET_DATA_BY_SEMATIC(cached_triangle[sub_index]->point, cached_vertex_out[t_index], SEMANTIC::SV_POSITION);
    }
    
    
    //cvv clip
    static std::vector<VertexOutput> clip_verteies;
    clip_verteies.clear();
    ClipTriangleDetail(clip_verteies, cached_triangle);
    if(clip_verteies.size() < 3) return;
    
    PerspectiveDivideAndViewPort(clip_verteies[0]);
    PerspectiveDivideAndViewPort(clip_verteies[1]);
    cached_triangle[0] = &clip_verteies[0];
    for (size_t t_index = 2; t_index < clip_verteies.size(); ++t_index)
    {
        PerspectiveDivideAndViewPort(clip_verteies[t_index]);
        cached_triangle[1] = &clip_verteies[t_index - 1];
        cached_triangle[2] = &clip_verteies[t_index];
        // back-face culling, 计算几何，判断线段的拐向， 矢量叉积
        if(IsBackFace(cached_triangle[0]->screen, cached_triangle[1]->screen, cached_triangle[2]->screen))
            continue;
        RasterizerTriangle();
    }
}

void XRender::Graphics::RasterizerTriangle()
{
    auto [lb, rt] = Math::TriangleBoundingBox(cached_triangle[0]->screen, cached_triangle[1]->screen, cached_triangle[2]->screen);
    lb.x = std::clamp(lb.x, 0, (int)render_context.GetWidth());
    lb.y = std::clamp(lb.y, 0, (int)render_context.GetHeight());
    rt.x = std::clamp(rt.x, 0, (int)render_context.GetWidth());
    rt.y = std::clamp(rt.y, 0, (int)render_context.GetHeight());

    Vec2f center_point;
    for(uint32_t x = lb.x; x < rt.x; ++x)
    {
        for(uint32_t y = lb.y; y < rt.y; ++y)
        {
            center_point.x = x + 0.5;
            center_point.y = y + 0.5;
            auto[alpha, beta, gamma] = Math::TriangleBarycentric(cached_triangle[0]->screen, cached_triangle[1]->screen, cached_triangle[2]->screen, center_point);
            if(alpha < 0 || beta < 0 || gamma < 0) continue;
            PropertyBarycentricInterpolation(Vec2i(x, y), Vec3f(alpha, beta, gamma));
        }
    }
}

void XRender::Graphics::PropertyBarycentricInterpolation(const Vec2i& point, const Vec3f& barycentric)
{
    float depth = Math::BarycentricInterpolation<float>(cached_triangle[0]->viewDepth, cached_triangle[1]->viewDepth, cached_triangle[2]->viewDepth, barycentric);
    //early depth test
    if(!DepthTest(point.x, point.y, depth)) return;

    float viewZ = (barycentric.x / cached_triangle[0]->viewZ + barycentric.y / cached_triangle[1]->viewZ + barycentric.z / cached_triangle[2]->viewZ);
    float A = barycentric.x / (cached_triangle[0]->viewZ * viewZ);
    float B = barycentric.y / (cached_triangle[1]->viewZ * viewZ);
    float G = barycentric.z / (cached_triangle[2]->viewZ * viewZ);

    fragment_input.screen.x = point.x; fragment_input.screen.y = point.y;
    fragment_input.viewDepth = depth;
    fragment_input.viewZ = viewZ;
    BarycentrixInterpolationVertex(fragment_input, cached_triangle, Vec3f(A, B, G));
    ExecuteFragmentShader();
}

void XRender::Graphics::ExecuteFragmentShader()
{
    Shader* shader = shader_map[current_execute_vbo_id];
    static Color color;
    shader->Fragment(fragment_input, color);
    ApplyFragment(fragment_input.screen.x, fragment_input.screen.y, color, fragment_input.viewDepth);
}

void XRender::Graphics::ApplyFragment(const uint32_t& x, const uint32_t& y, const Color& color, const float& depth)
{
    render_context.ActivedRenderTexture()->RenderPixel(x, y, color, depth);
}

void XRender::Graphics::ActiveRender(const uint32_t& vbo_id)
{
    active_buffers.emplace(vbo_id);
}

void XRender::Graphics::Present()
{
    auto device = RenderDevice::Device();
    assert(device != nullptr);
    assert(render_context.GetWidth() == device->GetWidth());
    assert(render_context.GetHeight() == device->GetHeight());
    device->OnPresent(&render_context);
}

XRender::Graphics& XRender::Graphics::VirtualGraphic()
{
	static XRender::Graphics virtual_graphic;
	return virtual_graphic;
}