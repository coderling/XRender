#pragma once
#include<geometry.h>
#include <memory>

#include "Mesh.h"
#include "Semantic.h"

namespace XRender
{

class Shader
{
public:
    template<class T>
    static std::unique_ptr<Shader> CreateShader()
    {
        return std::make_unique<T>();
    }

    virtual ~Shader();
     Shader();
protected:
    uint32_t vertex_intput_semantic = 0;
    uint32_t vertex_output_semantic = 0;
    bool HasVertexInputSemantic(const SEMANTIC& semantic) const;
    bool HasVertexOutputSemantic(const SEMANTIC& semantic) const;
    virtual void Init() = 0;
    virtual VertexOutput Vertex(const VertexInput& in) = 0; 
    virtual void Fragment(const VertexOutput& in, Color& color) = 0;

    std::map<SEMANTIC, std::function<void(VertexOutput& out, VertexOutput* triangle[], const SEMANTIC& semantic, const Vec3f& barycentric)>> propertory_interpolation_funcs;
    friend class Graphics;
};
}