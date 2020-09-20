#include "Shader.h"
#include <type_traits>

XRender::Shader::~Shader(){}
XRender::Shader::Shader()
{
    BIND_VERTEX_INPUT(SEMANTIC::POSITION);
}

bool XRender::Shader::HasVertexInputSemantic(const SEMANTIC& semantic) const
{
    return (vertex_intput_semantic & (1 << static_cast<uint32_t>(semantic))) != 0;
}

void XRender::Shader::AddPass(const std::string& name, const VertFunctionType& vert, const FragmentFunctionType& frament)
{
    assert(names.count(name) == 0);
    names.emplace(name);
    verts.emplace_back(vert);
    fragments.emplace_back(frament);
}