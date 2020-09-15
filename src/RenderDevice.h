#pragma once
#include <stdint.h>
#include <string>

#include "Color.h"
#include "RenderContext.h"

namespace XRender
{
    class RenderDevice
    {
    public:
        static RenderDevice* Device();
        static void Setup(const std::string& name);
        virtual ~RenderDevice();
        void Init(const uint32_t& width, const uint32_t& height);
        virtual void OnPresent(const RenderContext* context) = 0;
        virtual void OnUpdate() = 0;
        const uint32_t& GetWidth() const;
        const uint32_t& GetHeight() const;
    protected:
        RenderDevice(const std::string& name);
        virtual void OnInit() = 0;
        uint32_t width;
        uint32_t height;
        std::string name;
    };
}