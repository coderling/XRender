#pragma once
#include<geometry.h>
#include <memory>
#include <string>
#include <any>

#include "Mesh.h"
#include "Texture2D.h"
#include "Sampler2D.h"
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
            auto ret = static_cast<std::unique_ptr<Shader>>(std::make_unique<T>());
            ret->Init();
            return ret;
        }

        template<typename T>
        void SetUniform(const std::string& field_name, T&& value)
        {
            const auto &iter = uniforms.find(field_name);
            if (iter != uniforms.end()) 
            {
              this->*(std::any_cast<T Shader::*>(iter->second)) = std::forward<T>(value);
            }
        }
        
        template<typename T>
        void SetUniform(const std::string& field_name, T* value)
        {
            const auto &iter = uniforms.find(field_name);
            if (iter != uniforms.end()) 
            {
                this->*(std::any_cast<T Shader::*>(iter->second)) = value;
            }
        }
        
        template<>
        void SetUniform(const std::string& field_name, Texture2D* value)
        {
            const auto &iter = uniforms.find(field_name);
            if (iter != uniforms.end()) 
            {
                (this->*(std::any_cast<Sampler2D Shader::*>(iter->second))).AttachTexture(value);
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

        std::unordered_map<std::string, std::any> uniforms;
    private:
        friend class Graphics;
    };


    class Pass
    {
    public:
        virtual void vert(const VertexInput& in, VertexOutput& out) = 0;
        virtual void fragment(const VertexOutput& in, Color& out) = 0;
    };


    class ShaderV
    {
    public:
        virtual ShaderV* Instance() = 0;
        std::unordered_map<std::string, std::any> uniforms;
        
        std::vector<Pass> pasies;
        static std::unordered_map<std::string, Shader*> shaders;
        friend class Graphics;

    };



    #define UN(T,name) static T name

    #define BEGIN_PASS(name)\
        public:\
        class Pass##name : XRender::Pass\
        {\

    #define VERT(logic)\
        void vert(const VertexInput& in, VertexOutput& out) override\
        {\
            logic\
        }

    #define FRAGMENT(logic)\
        void fragment(const VertexOutput& in, Color& out) override\
        {\
            logic\
        }

    #define END_PASS()\
        };

    class ShaderTest :ShaderV
    {
            UN(Vec3f, t);
            BEGIN_PASS(t1)
            VERT(
                int a = 0;
                out.point.x = 0;
                t.x = 0;
                const Vec3f& t = in.data.Get(SEMANTIC::SV_POSITION);
                
            )
            FRAGMENT()
            END_PASS()
        ShaderV* Instance() override{
            static ShaderTest shader("test");
            return &shader;
        }
        private:
            ShaderTest(std::string name):ShaderV()
            {
            }
    };
    
}
