#pragma once
#include <geometry.h>

#include "Lighting.h"

namespace XRender::GraphicsGlobalData
{
    Matrix matrix_m;
    Matrix matrix_v;
    Matrix matrix_p;
    Matrix matrix_mvp;
    Matrix matrix_vp;
    Matrix matrix_mv;
    Matrix matrix_viewport;
    Lighting::LightData lights[Lighting::max_light_num];
    Lighting::LightData* light; 
}