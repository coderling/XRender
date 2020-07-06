#pragma once
#include <memory>
#include <string>

#include "Shader.h"
#include "Texture2D.h"
#include "Sampler2D.h"

namespace XRender
{

class Matrial
{
public:
    template<typename T>
    void SetAtrribute(const std::string& name, T&& value)
    {
        assert(shader != nullptr);
        shader->SetUniform(name, std::forward<T>(value));
    }

    template<typename T>
    void SetAtrribute(const std::string& name, std::unique_ptr<T> value)
    {
        assert(shader != nullptr);
        shader->SetUniform(name, value.release());
    }
    
    template<typename T>
    void SetAtrribute(const std::string& name, T* value)
    {
        assert(shader != nullptr);
        shader->SetUniform(name, value);
    }
    
    std::unique_ptr<Shader> shader;
};

}