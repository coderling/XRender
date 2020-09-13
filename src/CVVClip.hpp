#pragma once

#include <vector>

#include "Semantic.h"
#include "math/Math.h"

namespace XRender
{
    static const float w_zero = 1e-5;

    inline float LerpValue(const float& w1, const float& w2)
    {
        // w = w1 + (w2 - w1) * t; make w = 1e-10 , get t
        return (w_zero - w1) / (w2 - w1);
    }

    inline Vec4f IntersectionPoint(const Vec4f& p1, const Vec4f& p2, const float& t)
    {
        Vec4f ret;
        ret.x = Math::LinearInterpolation(p1.x, p2.x, t);
        ret.y = Math::LinearInterpolation(p1.y, p2.y, t);
        ret.z = Math::LinearInterpolation(p1.z, p2.z, t);
        ret.w = Math::LinearInterpolation(p1.w, p2.w, t);
        return ret;
    }

    inline bool IsInSide(const Vec4f& point)
    {
        return point.w >= w_zero;
    }

    inline bool IsInCVV(const Vec4f& point)
    {
        return std::abs(point.x) <= point.w && std::abs(point.y) <= point.w && std::abs(point.z) <= point.w;
    }

    uint32_t SutherlandHodgman(std::vector<VertexOutput>& out_verteies, VertexOutput **triangle, const Vec4f* points, const uint32_t count)
    {
        for(uint32_t index = 0; index < count; ++index)
        {
            const auto& current = points[index];
            const uint32_t& pre_index = (index + count - 1) % count;
            const auto& prev = points[pre_index];
            const float& t = LerpValue(prev.w, current.w);
            auto p = IntersectionPoint(prev, current, t);
            const bool& current_in = IsInSide(current);
            const bool& prev_in = IsInSide(prev);
            
            VertexOutput intersect_vertex;
			VertexOutput* current_vertex = triangle[index];
			VertexOutput* pre_vertex = triangle[pre_index];
            if(current_in)
            {
                if(!prev_in)
                {
                    LinearInterpolationVertex(intersect_vertex, *pre_vertex, *current_vertex, t);
                    out_verteies.emplace_back(intersect_vertex);
                }
                out_verteies.emplace_back(*current_vertex);
            }
            else if(prev_in)
            {
                LinearInterpolationVertex(intersect_vertex, *pre_vertex, *current_vertex, t);
                out_verteies.emplace_back(intersect_vertex);
            }
        }

        if (out_verteies.size() < 2) return 0;
        return out_verteies.size() - 2;
    }

    uint32_t ClipTriangleDetail(std::vector<VertexOutput>& out_verteies, VertexOutput **triangle, const Vec4f* points)
    {
        // clip near_plane first then clip w <= 0
        bool p1_in = IsInSide(points[0]);
        bool p2_in = IsInSide(points[1]);
        bool p3_in = IsInSide(points[2]);
        if(p1_in && p2_in && p3_in)
        {
            out_verteies.emplace_back(*(triangle[0]));
            out_verteies.emplace_back(*(triangle[1]));
            out_verteies.emplace_back(*(triangle[2]));
            return 1;
        }

        return SutherlandHodgman(out_verteies, triangle, points, 3);
    }
}