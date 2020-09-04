#pragma once

namespace XRender 
{
    class ShadowMap final
    {
    public:
        void Init();
    private:
        float* depth_buffer;
    };
}