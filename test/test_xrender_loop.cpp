#include <iostream>
#include <DiffuseColor.hpp>

#include "test_util.h"
#include "test_create_scene.h"
#include "PS_ShowDepth.hpp"

const bool IsTriangle = true;
const bool depth_only = false;

XRender::Object* p_obj = nullptr;
Vec3f rotation = Vec3f_Zero;

void Tick()
{
    if (p_obj != nullptr)
    {
        rotation.y += 1;
        //p_obj->Transform().SetRotation(rotation);
    }
}

void RenderSampleTriangle(XRender::Scene* scene)
{
    std::unique_ptr<XRender::Object> obj =  XRender::Test::LoadSampleTriangleAsObject();
    obj->Transform().SetPosition(Vec3f(0, 0, -0.1));
    p_obj = obj.get();
    scene->AddObject(std::move(obj));
    //XRender::Camera::MainCamera().IsPerspective(false);
}

void RenderSampleObject(XRender::Scene* scene)
{
    auto object = XRender::Test::LoadSampleObject<XRender::Shaders::DiffuseColor>();
    object->Transform().SetPosition(Vec3f(0, 0, -3));
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
    object->Transform().SetRotation(rotation);
    p_obj = object.get();
    scene->AddObject(std::move(object));
}

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene("Diffuse", Tick);
	if (IsTriangle)
		RenderSampleTriangle(render.GetPipeline()->scene.get());
    else
        RenderSampleObject(render.GetPipeline()->scene.get());
    
    if(depth_only)
    {
        XRender::PostProcess::AddPostProcessEffect<XRender::PostProcessing::PS_ShowDepth>(&XRender::Camera::MainCamera());
    }

    render.Loop();
    return 0;
}