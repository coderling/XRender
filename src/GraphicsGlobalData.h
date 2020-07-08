#pragma once
#include <geometry.h>

#include "Lighting.h"

namespace XRender::GraphicsGlobalData
{
    extern Matrix matrix_m;
    extern Matrix matrix_v;
    extern Matrix matrix_p;
    extern Matrix matrix_mvp;
    extern Matrix matrix_vp;
    extern Matrix matrix_mv;
    extern Matrix matrix_viewport;
    extern Lighting::LightData lights[Lighting::max_light_num];
    extern Lighting::LightData* light;
}