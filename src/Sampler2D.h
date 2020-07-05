#pragma once

#include "Texture2D.h"
#include "Color.h"

namespace XRender
{
    class Sampler2D
    {
    public:
        Sampler2D(const Texture2D* texture);
        Color Point(const float& u, const float& v); 
    private:
        const Texture2D* texture;
    };
}