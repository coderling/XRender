
#include <iostream>

#include <PixelLambert.hpp>

#include "test_util.h"
#include "test_create_scene.h"

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene("LambertLight", [] {});
    auto object = XRender::Test::LoadSampleObject<XRender::Shaders::PixelLambert>();
    object->SetPosition(Vec3f(0, 0, -3));
    render.GetPipeline()->scene->AddObject(std::move(object));
    XRender::Test::ConfigSceneLight(render.GetPipeline()->scene.get());
    render.Loop();
    return 0;
}