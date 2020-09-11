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
        rotation.y += 10;
        //p_obj->SetRotation(rotation);
    }
}

void RenderSampleTriangle(XRender::Scene* scene)
{
    std::unique_ptr<XRender::Object> obj =  XRender::Test::LoadSampleTriangleAsObject();
    p_obj = obj.get();
    scene->AddObject(std::move(obj));
}

void RenderSampleObject(XRender::Scene* scene)
{
    auto object = XRender::Test::LoadSampleObject<XRender::Shaders::DiffuseColor>();
    object->SetPosition(Vec3f(0, 0, -3));
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