#pragma once
#include <geometry.h>

namespace XRender::Shapes
{
    struct ShapeData
    {
        ShapeData(const uint32_t& vertex_count, const uint32_t& index_count,
                  const Vec3f* verteices, const Vec3f* normals,
                  const Vec2f* uv, const uint32_t* indeics);

        const uint32_t vertex_count;
        const uint32_t index_count;
        const Vec3f* verteices;
        const Vec3f* normals;
        const Vec2f* uv;
        const uint32_t* indeics;
    };

    #define DECLAR_GETDATA public:\
                                static const ShapeData& GetShapeData()

    #define DEFINE_GETDATA(T) const XRender::Shapes::ShapeData& XRender::Shapes::T::GetShapeData()\
                              {\
                                static XRender::Shapes::ShapeData data(vertex_count, index_count, verteices, normals, uv, indeics);\
                                return data;\
                              }
}