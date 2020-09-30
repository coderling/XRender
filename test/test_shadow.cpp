#include <iostream>

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
	light->Position(Vec3f(0, 2, 7));
	light->Rotation(Vec3f(30, 180, 0));
	light->Enable();
}

void ConfigSceneObjects(XRender::Scene* scene)
{
    std::unique_ptr<XRender::Object> object = XRender::Test::LoadSampleObject<XRender::Shaders::PixelLambert>();
    object->Transform().SetPosition(Vec3f(0, 1, 0));
    object->Transform().SetRotation(Vec3f(0, 0, 0));
    scene->AddObject(std::move(object));
    
    std::unique_ptr<XRender::Object> cube = XRender::Shapes::CreateShape<XRender::Shapes::Cube>();
    cube->Renderer()->mat = std::make_unique<XRender::Matrial>();
    cube->Renderer()->mat->shader = XRender::Shader::CreateShader<XRender::Shaders::PixelLambert>();
    cube->Renderer()->mat->SetAtrribute("color", XRender::CColor::RED);
    cube->Transform().SetPosition(Vec3f(-2, 0.5, 2));
    cube->Transform().SetRotation(Vec3f(0, 45, 0));
    scene->AddObject(std::move(cube));
    
    std::unique_ptr<XRender::Object> sphere = XRender::Shapes::CreateShape<XRender::Shapes::Sphere>();
    sphere->Renderer()->mat = std::make_unique<XRender::Matrial>();
    sphere->Renderer()->mat->shader = XRender::Shader::CreateShader<XRender::Shaders::PixelLambert>();
    sphere->Renderer()->mat->SetAtrribute("color", XRender::CColor::GREEN);
    sphere->Transform().SetPosition(Vec3f(2, 0.8, 2));
    sphere->Transform().SetRotation(Vec3f(0, 45, 0));
    scene->AddObject(std::move(sphere));

    std::unique_ptr<XRender::Object> panel = XRender::Shapes::CreateShape<XRender::Shapes::Panel>();
    panel->Renderer()->mat = std::make_unique<XRender::Matrial>();
    panel->Renderer()->mat->shader = XRender::Shader::CreateShader<XRender::Shaders::PixelLambert>();
    panel->Transform().SetPosition(Vec3f(0, 0, 0));
    panel->Transform().SetRotation(Vec3f(0, 0, 0));
    scene->AddObject(std::move(panel));
}

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene("Shadow", [] {});
    ConfigLight(render.GetPipeline()->scene.get());
    ConfigSceneObjects(render.GetPipeline()->scene.get());
    /*
    XRender::Camera::MainCamera().Position(Vec3f(0, 2, 18));
    XRender::Camera::MainCamera().Rotation(Vec3f(0, 180, 0));
    XRender::Camera::MainCamera().IsPerspective(false);
    Matrix p = XRender::Camera::MainCamera().ProjMatrix();
    */
    XRender::Camera::MainCamera().LookAt(Vec3f(0, 2, 7), Vec3f(0, 1, 0), Vec3f(0, 2, 0));
    render.Loop();
    return 0;
}