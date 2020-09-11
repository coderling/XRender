#pragma once

#include <stdint.h>

namespace XRender::GraphicsEnum
{
    enum struct EDepthTestMethod : uint32_t
    {
        Less = 0,
        Greater = 1,
        LessEqual = 2,
        GreaterEqual = 3,
        Equal = 4, 
        NotEqual = 5,
        Always = 6,
    };


    enum EClearFlag 
    {
        Clear_None = 0,
        Clear_Color = 1 << 0,
        Clear_Depth = 1 << 1,
    };
}