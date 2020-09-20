#pragma once
#include<geometry.h>
#include <memory>
#include <string>
#include <any>
#include <functional>
#include <unordered_set>
#include <optional>

#include "Mesh.h"
#include "Texture2D.h"
#include "Sampler2D.h"
#include "Semantic.h"

namespace XRender
{
    typedef std::function<void(const XRender::VertexInput& in, XRender::VertexOutput& out)> VertFunctionType;
    typedef std::function<void(const XRender::VertexOutput& in, XRender::Color& out)> FragmentFunctionType;
    
    #define REGISTER_UNIFORM(T, field_name)\
        auto field_address = static_cast<T Shader::*>(&std::remove_pointer<decltype(this)>::type::field_name);\
        uniform_address.insert_or_assign(#field_name, field_address)\

    class Shader
    {
    public:
        template<class T>
        static std::unique_ptr<Shader> CreateShader()
        {
            auto ret = static_cast<std::unique_ptr<Shader>>(std::make_unique<T>());
            ret->Init();
            ret->SetPass();
            return ret;
        }

        template<typename T>
        void SetUniform(const std::string& field_name, T&& value)
        {
            const auto &iter = uniform_address.find(field_name);
            if (iter != uniform_address.end()) 
            {
              this->*(std::any_cast<T Shader::*>(iter->second)) = std::forward<T>(value);
            }
        }
        
        template<typename T>
        void SetUniform(const std::string& field_name, T* value)
        {
            const auto &iter = uniform_address.find(field_name);
            if (iter != uniform_address.end()) 
            {
                this->*(std::any_cast<T Shader::*>(iter->second)) = value;
            }
        }
        
        template<>
        void SetUniform(const std::string& field_name, Texture2D* value)
        {
            const auto &iter = uniform_address.find(field_name);
            if (iter != uniform_address.end()) 
            {
                (this->*(std::any_cast<Sampler2D Shader::*>(iter->second))).AttachTexture(value);
            }
        }
        
        
        virtual ~Shader();
         Shader();
    protected:
        virtual void SetPass() = 0;
        virtual void Init() = 0;
        void AddPass(const std::string& name, const VertFunctionType&, const FragmentFunctionType&);
        bool HasVertexInputSemantic(const SEMANTIC& semantic) const;
        const std::string shadow_pass_name = "ShadowCaster";
        uint32_t vertex_intput_semantic;
        std::unordered_set<std::string> names;
        std::vector<VertFunctionType> verts;
        std::vector<FragmentFunctionType> fragments;
        std::optional<VertFunctionType> shadow_vert;
        std::optional<FragmentFunctionType> shadow_fragment;
        std::unordered_map<std::string, std::any> uniform_address;
    private:
        friend class Graphics;
    };


    #define SET_PASIES()\
    protected:\
        void SetPass() override\
        {\
        

    #define VERT_HEAD(name)\
        VertFunctionType name = [&](const VertexInput& in, VertexOutput& out)
    
    #define FRAGMENT_HEAD(name)\
            FragmentFunctionType name = [&](const VertexOutput& in, Color& out)

    #define END_PASS()\

    #define END_SET_PASIES()\
        }\

    #define BIND_VERTEX_INPUT(semantic)\
        this->vertex_intput_semantic |= 1 << static_cast<uint32_t>(semantic);
}
