#pragma once
#include <string>
#include <memory>

#include "../../RenderDevice.h"

#include "../image/ImageDevice.h"
#ifdef WIN32
#include "../win/WindowsDevice.h"
#endif

namespace XRender
{
    #ifdef USE_IMAGE_TARGET 
    typedef ImageDevice DeviceType;
    #elif WIN32
    typedef WindowsDevice DeviceType;
    #else
    typedef ImageDevice DeviceType;
    #endif
}
