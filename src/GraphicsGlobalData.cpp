#pragma once
#include <geometry.h>

#include "Lighting.h"

namespace XRender::GraphicsGlobalData
{
    Vec4f zbuffer_args;
    Matrix matrix_m;
    Matrix matrix_v;
    Matrix matrix_p;
    Matrix matrix_mvp;
    Matrix matrix_vp;
    Matrix matrix_mv;
    Matrix matrix_viewport;
    Matrix matrix_shadow_light_vp;
    uint32_t shadow_light_index;
    const Lighting::LightData* lights[Lighting::max_light_num]; 
    uint32_t light_count;
}