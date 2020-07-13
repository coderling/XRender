#include "ShapeData.h"

XRender::Shapes::ShapeData::ShapeData(const uint32_t& vertex_count, const uint32_t& index_count,
                  const Vec3f* verteices, const Vec3f* normals,
                  const Vec2f* uv, const uint32_t* indeics): 
                  vertex_count(vertex_count), index_count(index_count),
                  verteices(verteices), normals(normals),
                  uv(uv), indeics(indeics)
                  {}
            