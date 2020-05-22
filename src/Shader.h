#pragma once
#include<geometry.h>
#include "Mesh.h"

class IShader
{
public:
    virtual ~IShader();
    virtual void Shade(void* in, Vec3f& color) = 0;
};

template<class Output, class Input>
class Shader: public IShader
{
public:
    virtual ~Shader(){}
    void Shade(void* in, Vec3f& color) override
    {
        Output out = Vertex(static_cast<Input> (*in));
        Fragment(out, color);
    }
protected:
    Output Vertex(Input in) = 0; 
    void Fragment(Output in, Vec3f &color) = 0;
};