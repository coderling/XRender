
#include <iostream>

#include <PixelLambert.hpp>

#include "test_util.h"


int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene<XRender::Shaders::PixelLambert>("LambertLight");
    XRender::Test::ConfigSceneLight(render.GetPipeline()->scene.get());
    render.Loop();
    return 0;
}