#pragma once
#include <string>
#include <memory>

#include "../../RenderDevice.h"

#ifdef USE_IMAGE_TARGET 
#include "../image/ImageDevice.h"
#elif WIN32
#include "../win/WindowsDevice.h"
#else
#include "../image/ImageDevice.h"
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
