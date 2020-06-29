#pragma once
#include <memory>

#include "Shader.h"

namespace XRender
{

class Matrial
{
public:
    std::unique_ptr<Shader> shader;
};

}