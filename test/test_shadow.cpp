#include <Pipeline.h>
#include <PixelLambert.hpp>
#include <ColorShader.hpp>

#include "test_util.h"
#include "test_create_scene.h"

void ConfigLight(XRender::Scene* scene)
{
    const auto light = scene->GetLight(0);
    auto data = light->GetData();
    data->color = XRender::CColor::Wihte;
    data->intensity = 1;
    data->range = 0;
    data->world_pos = Vec4f(0, 0, -1, 0);
    light->Enable();
}

void ConfigSceneObjects(XRender::Scene* scene)
{
    /*
    std::unique_ptr<XRender::Object> object = XRender::Test::LoadSampleObject<XRender::Shaders::PixelLambert>();
    object->SetPosition(Vec3f(0, 0, -3));
    scene->AddObject(std::move(object));
    */
    XRender::Test::LoadSampleTriangleAsObject(scene);
    
    std::unique_ptr<XRender::Object> cube = XRender::Shapes::CreateShape<XRender::Shapes::Cube>();
    cube->renderer->mat = std::make_unique<XRender::Matrial>();
    cube->renderer->mat->shader = XRender::Shader::CreateShader<XRender::Shaders::ColorShader>();
    cube->SetPosition(Vec3f(0, 0, -2));
    scene->AddObject(std::move(cube));
    
}

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene("Shadow");
    ConfigLight(render.GetPipeline()->scene.get());
    ConfigSceneObjects(render.GetPipeline()->scene.get());
    render.Loop();
    return 0;
}