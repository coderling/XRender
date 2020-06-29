#include "Shader.h"

XRender::Shader::~Shader(){}
XRender::Shader::Shader()
{
    BIND_VERTEXINPUT_SEMANTIC(SEMANTIC::POSITION, Vec4f);
	BIND_VERTEXOUTPUT_SEMANTIC(SEMANTIC::SV_POSITION, Vec4f);
}

bool XRender::Shader::HasVertexInputSemantic(const SEMANTIC& semantic) const
{
    return (vertex_intput_semantic | static_cast<uint32_t>(semantic)) != 0;
}

bool XRender::Shader::HasVertexOutputSemantic(const SEMANTIC& semantic) const
{
    return (vertex_output_semantic | static_cast<uint32_t>(semantic)) != 0;
}