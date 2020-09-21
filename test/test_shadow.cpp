#include <Pipeline.h>
#include <PixelLambert.hpp>
#include <ColorShader.hpp>

#include "test_util.h"
#include "test_create_scene.h"

void ConfigLight(XRender::Scene* scene)
{
    const auto light = scene->GetLight(0);
    light->LightColor(XRender::CColor::Wihte);
	light->Intensity(1);
	light->SetLightType(XRender::Lighting::LightType::Directional);
	light->Position(Vec3f(0, 3, -7));
	light->Rotation(Vec3f(45, 45, 0));
	light->Enable();
}

void ConfigSceneObjects(XRender::Scene* scene)
{
    std::unique_ptr<XRender::Object> object = XRender::Test::LoadSampleObject<XRender::Shaders::PixelLambert>();
    object->Transform().SetPosition(Vec3f(0, 1, 0));
    object->Transform().SetRotation(Vec3f(0, 180, 0));
    scene->AddObject(std::move(object));

    std::unique_ptr<XRender::Object> cube = XRender::Shapes::CreateShape<XRender::Shapes::Panel>();
    cube->Renderer()->mat = std::make_unique<XRender::Matrial>();
    cube->Renderer()->mat->shader = XRender::Shader::CreateShader<XRender::Shaders::PixelLambert>();
    cube->Transform().SetPosition(Vec3f(0, 0, 0));
    cube->Transform().SetRotation(Vec3f(0, 0, 0));
    scene->AddObject(std::move(cube));
}

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene("Shadow", [] {});
    ConfigLight(render.GetPipeline()->scene.get());
    ConfigSceneObjects(render.GetPipeline()->scene.get());
    //XRender::Camera::MainCamera().Position(Vec3f(-60.1138077, 56.0389252, -101.624115));
    //XRender::Camera::MainCamera().Rotation(Vec3f(45, 45, 0));
    //XRender::Camera::MainCamera().IsPerspective(false);
    XRender::Camera::MainCamera().LookAt(Vec3f(0, 2, -7), Vec3f(0, 1, 0), Vec3f(0, 2, 0));
    render.Loop();
    return 0;
}