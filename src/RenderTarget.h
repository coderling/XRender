#pragma once
#include <stdint.h>

#include "Color.h"

namespace XRender
{
    class RenderTarget
    {
    public:
        virtual ~RenderTarget();
        void Init(const uint32_t& width, const uint32_t& height);
        virtual void OnPresent(const Color* frame_buffer) = 0;
        const uint32_t& GetWidth() const;
        const uint32_t& GetHeight() const;
    protected:
        virtual void OnInit() = 0;
        uint32_t width;
        uint32_t height;
    };
}