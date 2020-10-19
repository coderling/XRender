#include "Semantic.h"

void XRender::BarycentrixInterpolationVertex(XRender::VertexOutput& out, XRender::VertexOutput* triangle[], const Vec3f& barycentric)
{
    for(uint32_t st = static_cast<uint32_t>(XRender::SEMANTIC::POSITION); st < static_cast<uint32_t>(XRender::SEMANTIC::MAX); ++st)
    {
        assert(triangle[0] != nullptr || triangle[1] != nullptr || triangle[2] != nullptr);
        assert((triangle[0]->data.semantics ^  triangle[1]->data.semantics) == 0
               || (triangle[0]->data.semantics ^  triangle[2]->data.semantics) == 0
               || (triangle[1]->data.semantics ^  triangle[2]->data.semantics) == 0);
        if((triangle[0]->data.semantics & (1 << st)) == 0)
            continue;
        static Vec4f property;
        const auto& property1 = (*(triangle[0])).data.data[st];
        const auto& property2 = (*(triangle[1])).data.data[st]; 
        const auto& property3 = (*(triangle[2])).data.data[st];
        const auto& size = (*(triangle[0])).data.Size(static_cast<XRender::SEMANTIC>(st));
        for(uint32_t index = 0; index < size; ++index)
        {
            property[index] = XRender::Math::BarycentricInterpolation(property1[index], property2[index], property3[index], barycentric);
        }
        out.Set(static_cast<XRender::SEMANTIC>(st), property);
    }
}
    
void XRender::LinearInterpolationVertex(XRender::VertexOutput& out, XRender::VertexOutput& v1, XRender::VertexOutput& v2, const float& t)
{
    for(uint32_t st = static_cast<uint32_t>(XRender::SEMANTIC::POSITION); st < static_cast<uint32_t>(XRender::SEMANTIC::MAX); ++st)
    {
        assert((v1.data.semantics ^  v2.data.semantics) == 0);
        if((v1.data.semantics & (1 << st)) == 0)
            continue;
        Vec4f property;
        const auto& property1 = v1.data.data[st];
        const auto& property2 = v2.data.data[st];
        const uint32_t& size = property1.size();
        for(uint32_t index = 0; index < size; ++index)
        {
            property[index] = (XRender::Math::LinearInterpolation(property1[index], property2[index], t));
        }
        out.Set(static_cast<XRender::SEMANTIC>(st), property);
    }

}