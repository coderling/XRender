#include <iostream>
#include <DiffuseColor.hpp>

#include "test_util.h"

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene("Diffuse");
    auto object = XRender::Test::LoadSampleObject<XRender::Shaders::DiffuseColor>();
    object->SetPosition(Vec3f(0, 0, -3));
    render.GetPipeline()->scene->AddObject(std::move(object));
    render.Loop();
    return 0;
}