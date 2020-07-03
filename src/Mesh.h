#pragma once
#include <geometry.h>
#include <stdint.h>
#include <vector>
#include <optional>

#include "Vertex.h"
#include "Color.h"
#include "./resources/ILoader.h"

namespace XRender
{

class Mesh
{
public:
    uint32_t GetVertexCount() const;
    const std::vector<Vec3f>& GetPositions() const;
    const std::vector<uint32_t>& GetIndeies() const;
    const std::optional<std::vector<Color>>& GetColors() const;
    const std::optional<std::vector<Vec3f>>& GetNormals() const;
    const std::optional<std::vector<Vec2f>>& GetUV() const;
    const std::optional<std::vector<Vec2f>>& GetUV2() const;
    void SetPositions(const std::vector<Vec3f>& points);
    void SetIndeies(const std::vector<uint32_t>& indeies);
    void SetColors(std::vector<Color>& colors) ;
    void SetNormals(const std::vector<Vec3f>& normalsh) ;
    void SetUV(const std::vector<Vec2f>& uvs);
    void SetUV2(const std::vector<Vec2f>& uvs);
    void GetVertexByIndex(Vertex& vertex, const uint32_t& index) const;
private:
    std::vector<Vec3f> positions;
    std::vector<uint32_t >indeies;
    std::optional<std::vector<Vec3f>> normals;
    std::optional<std::vector<Color>> colors;
    std::optional<std::vector<Vec2f>> uv;
    std::optional<std::vector<Vec2f>> uv2;
    uint32_t vertex_count;
    friend class Res::ILoader<Mesh>;
};

}