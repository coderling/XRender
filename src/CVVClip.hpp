#pragma once

#include <vector>
#include "Semantic.h"

namespace XRender
{
    static const float w = 1e-10;

    enum EClipPlane
    {
        Near_Plane,
        Left_Plane,
        Right_Plane,
        Bottom_Plane,
        Top_Plane,
    };

    inline float LerpValue(const float& w1, const float& w2)
    {
        // w = w1 + (w2 - w1) * t; make w = 1e-10 , get t
        return (w - w1) / (w2 - w1);
    }

    inline float LinearLerp(const float& v1, const float& v2, const float& t)
    {
        return v1 + (v2 - v1) * t;
    }

    inline Vec4f IntersectionPoint(const Vec4f& p1, const Vec4f& p2)
    {
        Vec4f ret;
        const float& t = LerpValue(p1.w, p2.w);
        ret.w = w;
        ret.x = LinearLerp(p1.x, p2.x, t);
        ret.y = LinearLerp(p1.y, p2.y, t);
        ret.z = LinearLerp(p1.z, p2.z, t);
        return ret;
    }

    bool IsInside(const EClipPlane& plane, const Vec4f& point)
    {
        switch (plane) {
            case EClipPlane::Near_Plane:
                return point.w >= w;
            case EClipPlane::Left_Plane:
                return point.x >= -point.w;
            case EClipPlane::Right_Plane:
                return point.x <= point.w;
            case EClipPlane::Bottom_Plane:
                return point.y >= -point.w;
            case EClipPlane::Top_Plane:
                return point.y <= point.w;
            default:
                return false;
        }
    }

    void ClipByPlane(const EClipPlane& plane, VertexOutput **triangle, const Vec4f* points)
    {
        for(uint32_t index = 0; index < 3; ++index)
        {

        }
    }

    inline bool IsInCVV(const Vec4f& point)
    {
        return std::abs(point.x) <= w && std::abs(point.y) <= w && std::abs(point.z) <= w;
    }

    void ClipTriangleDetail(std::vector<VertexOutput>& out_verteies, VertexOutput **triangle, const Vec4f* points)
    {
        bool p1_in = IsInCVV(points[0]);
        bool p2_in = IsInCVV(points[1]);
        bool p3_in = IsInCVV(points[2]);
        if(p1_in && p2_in && p3_in)
        {
            out_verteies.emplace_back(*(triangle[0]));
            out_verteies.emplace_back(*(triangle[1]));
            out_verteies.emplace_back(*(triangle[2]));
            return;
        }

        
    }
}