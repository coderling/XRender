#pragma once
#include<geometry.h>
#include <memory>
#include <string>
#include <any>

#include "Mesh.h"
#include "Semantic.h"

namespace XRender
{
    #define REGISTER_UNIFORM(T, field_name)\
        auto field_address = static_cast<T Shader::*>(&std::remove_pointer<decltype(this)>::type::field_name);\
        uniforms.insert_or_assign(#field_name, field_address)\

    class Shader
    {
    public:
        template<class T>
        static std::unique_ptr<Shader> CreateShader()
        {
            return std::make_unique<T>();
        }

        template<typename T>
        void SetUniform(const std::string& field_name, const T& value)
        {
            const auto &iter = uniforms.find(field_name);
            if (iter != uniforms.end()) 
            {
              this->*(std::any_cast<T Shader::*>(iter->second)) = value;
            }
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
        std::map<std::string, std::any> uniforms;
    private:
        friend class Graphics;
    };
}
