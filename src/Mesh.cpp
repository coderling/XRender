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

void XRender::Mesh::SetPositions(const std::vector<Vec3f>& points)
{
    positions.clear();
    for (const auto& v : points)
    {
        positions.emplace_back(v);
    }
}

void XRender::Mesh::SetIndeies(const std::vector<uint32_t>& indeies)
{
    this->indeies.clear();
    this->vertex_count = indeies.size();
    for (const auto& index : indeies)
    {
        this->indeies.emplace_back(index);
    }
}

void XRender::Mesh::SetColors(std::vector<Color>& colors)
{
    if (!this->colors.has_value())
    {
        this->colors.emplace(std::vector<Color>());
    }

    this->colors->clear();
    for (const auto& color : colors)
    {
        this->colors->emplace_back(color);
    }
}

void XRender::Mesh::SetNormals(const std::vector<Vec3f>& normals)
{
    if (!this->normals.has_value())
    {
        this->normals.emplace(std::vector<Vec3f>());
    }

    this->normals->clear();
    for (const auto& normal: normals)
    {
        this->normals->emplace_back(normal);
    }
}

void XRender::Mesh::SetUV(const std::vector<Vec2f>& uvs)
{
    if (!this->uv.has_value())
    {
        this->uv.emplace(std::vector<Vec2f>());
    }

    this->uv->clear();
    for (const auto& uv : uvs)
    {
        this->uv->emplace_back(uv);
    }
}

void XRender::Mesh::SetUV2(const std::vector<Vec2f>& uvs)
{
    if (!this->uv2.has_value())
    {
        this->uv2.emplace(std::vector<Vec2f>());
    }

    this->uv2->clear();
    for (const auto& uv : uvs)
    {
        this->uv2->emplace_back(uv);
    }
}

void XRender::Mesh::GetVertexByIndex(Vertex &vertex, const uint32_t &index) const
{
    assert(index < vertex_count);
    vertex.pos = positions[indeies[index]];
    normals? vertex.normal = normals.value()[index] : Vec3f_Zero;
    colors? vertex.color = colors.value()[index] : CColor::BLACK;
    uv? vertex.uv = uv.value()[index] : Vec2f_Zero;
    uv2? vertex.uv2 = uv2.value()[index] : Vec2f_Zero;
}