#pragma once

#include <vector>

#include "Color.h"

namespace XRender 
{
    class Texture
    {
    public:
        virtual ~Texture();
        void SetColors(const std::vector<Color>& colors);
        void SetColor(const uint32_t& index, const Color& color);
        Color GetColor(const uint32_t& index) const;
        Color* GetColors() const;
        const uint32_t& Size() const;
    protected:
        void CreateBuffer(const uint32_t& size);
        Color* datas;
    private:
        uint32_t size;
    };
}
