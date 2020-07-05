#pragma once

#include "Texture2D.h"
#include "Color.h"

namespace XRender
{
    class Sampler2D
    {
    public:
        Sampler2D() = default;
        void AttachTexture(Texture2D* texture);
        Color Point(const float& u, const float& v); 
    private:
        Texture2D* texture;
    };
}