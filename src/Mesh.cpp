#include "Mesh.h"

uint32_t XRender::Mesh::GetVertexCount() const
{
    return vertex_count;
}

const std::vector<Vec3f>& XRender::Mesh::GetPositions() const
{
    return positions;
}

const std::vector<uint32_t>& XRender::Mesh::GetIndeies() const
{
    return indeies;
}

const std::optional<std::vector<XRender::Color>>& XRender::Mesh::GetColors() const
{
    return colors;
}

const std::optional<std::vector<Vec3f>>& XRender::Mesh::GetNormals() const
{
    return normals;
}

const std::optional<std::vector<Vec2f>>& XRender::Mesh::GetUV() const
{
    return uv;
}

const std::optional<std::vector<Vec2f>>& XRender::Mesh::GetUV2() const
{
    return uv2;
}

void XRender::Mesh::GetVertexByIndex(Vertex &vertex, const uint32_t &index) const
{
    assert(index < vertex_count);
    vertex.pos = positions[index];
    normals? vertex.normal = normals.value()[index] : Vec3f_Zero;
    colors? vertex.color = colors.value()[index] : CColor::BLACK;
    uv? vertex.uv = uv.value()[index] : Vec2f_Zero;
    uv2? vertex.uv2 = uv2.value()[index] : Vec2f_Zero;
}