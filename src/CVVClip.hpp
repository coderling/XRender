#pragma once

#include <vector>
#include <functional>

#include "Semantic.h"
#include "math/Math.h"

namespace XRender
{
    static const float w_zero = 1e-5;

    enum EClipPlane
    {
        POSITIVE_W = 0,
        NEGATIVE_Z,
        POSITIVE_Z,
        NEGATIVE_X,
        POSITIVE_X,
        NEGATIVE_Y,
        POSITIVE_Y,
    };

    static const std::function<bool(const Vec4f& point)> IsInPlane[7]{
        [](const Vec4f& point) { return point.w > w_zero; },
        [](const Vec4f& point) { return point.z >= -point.w; },
        [](const Vec4f& point) { return point.z <= point.w; },
        [](const Vec4f& point) { return point.x >= -point.w; },
        [](const Vec4f& point) { return point.x <= point.w; },
        [](const Vec4f& point) { return point.y >= -point.w; },
        [](const Vec4f& point) { return point.y <= point.w; },
    };
    
    static const std::function<float(const Vec4f& point1, const Vec4f& point2)> LerpRatio[7]{
        [](const Vec4f& point1, const Vec4f& point2) { return (w_zero - point1.w) / (point2.w - point1.w); }, // w == w_zero
        [](const Vec4f& point1, const Vec4f& point2) { return (point1.z + point1.w) / (point1.z + point1.w - point2.z - point2.w); }, // z == -w
        [](const Vec4f& point1, const Vec4f& point2) { return (point1.z - point1.w) / (point1.z - point1.w - point2.z + point2.w); }, // z == w
        [](const Vec4f& point1, const Vec4f& point2) { return (point1.x + point1.w) / (point1.x + point1.w - point2.x - point2.w); }, // x == -w
        [](const Vec4f& point1, const Vec4f& point2) { return (point1.x - point1.w) / (point1.x - point1.w - point2.x + point2.w); }, // x == w
        [](const Vec4f& point1, const Vec4f& point2) { return (point1.y + point1.w) / (point1.y + point1.w - point2.y - point2.w); }, // y == -w
        [](const Vec4f& point1, const Vec4f& point2) { return (point1.y - point1.w) / (point1.y - point1.w - point2.y + point2.w); }, // y == w
    };

    inline bool IsInSide(const Vec4f& point, const EClipPlane& plane)
    {
        return IsInPlane[plane](point);
    }

    inline bool IsInCVV(const Vec4f& point)
    {
        return std::abs(point.x) <= point.w && std::abs(point.y) <= point.w && std::abs(point.z) <= point.w;
    }

    void ClipTrianglePlane(std::vector<VertexOutput>& in_verteies, std::vector<VertexOutput>& out_verteies, const EClipPlane& plane)
    {
        out_verteies.clear();
        const auto& size = in_verteies.size();
        for(std::size_t index = 0; index < in_verteies.size(); ++index)
        {
            auto& current = in_verteies[index];
            const auto& prev_index = (index + size - 1) % size;
            auto& prev = in_verteies[prev_index];
            const bool& current_in = IsInSide(current.point, plane);
            const bool& prev_in = IsInSide(prev.point, plane);

            if(current_in)
            {
                if(!prev_in)
                {
                    VertexOutput intersect_vertex;
                    LinearInterpolationVertex(intersect_vertex, prev, current, LerpRatio[plane](prev.point, current.point));
                    GET_DATA_BY_SEMATIC(intersect_vertex.point, intersect_vertex, SEMANTIC::SV_POSITION);
                    out_verteies.emplace_back(intersect_vertex);
                }
                out_verteies.emplace_back(current);
            }
            else if(prev_in)
            {
                VertexOutput intersect_vertex;
                LinearInterpolationVertex(intersect_vertex, prev, current, LerpRatio[plane](prev.point, current.point));
                GET_DATA_BY_SEMATIC(intersect_vertex.point, intersect_vertex, SEMANTIC::SV_POSITION);
                out_verteies.emplace_back(intersect_vertex);
            }
        }
    }

    void ClipTriangleDetail(std::vector<VertexOutput>& out_verteies, VertexOutput **triangle)
    {
        // clip near_plane first then clip w <= 0
        std::vector<VertexOutput> in_verteies{
            *(triangle[0]),
            *(triangle[1]),
            *(triangle[2]),
        };

        if(IsInCVV(in_verteies[0].point)
            && IsInCVV(in_verteies[1].point)
            && IsInCVV(in_verteies[2].point))
            {
                out_verteies = in_verteies;
            }
        
        // clip z first
        ClipTrianglePlane(in_verteies, out_verteies, EClipPlane::NEGATIVE_Z);
        ClipTrianglePlane(out_verteies, in_verteies, EClipPlane::POSITIVE_Z);
        ClipTrianglePlane(in_verteies, out_verteies, EClipPlane::POSITIVE_W);
        ClipTrianglePlane(out_verteies, in_verteies, EClipPlane::NEGATIVE_X);
        ClipTrianglePlane(in_verteies, out_verteies, EClipPlane::POSITIVE_X);
        ClipTrianglePlane(out_verteies, in_verteies, EClipPlane::NEGATIVE_Y);
        ClipTrianglePlane(in_verteies, out_verteies, EClipPlane::POSITIVE_Y);
    }
}