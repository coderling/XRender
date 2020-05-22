#pragma once

#include "gl.h"
#include "tgaimage.h"

class ImageRenderContext: public RenderContext
{
private:
    TGAImage* pRtImage = nullptr;
}