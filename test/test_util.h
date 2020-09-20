#pragma once

#include <string>
#include <Platform.h>
#include <Pipeline.h>

#include "test_pipeline.h"

namespace XRender::Test 
{
    void InitSetCamera(Camera& camera)
    {
        camera.Angle(60.f);
        camera.Near(0.1f);
        camera.Far(500.f);
        camera.LookAt(Vec3f_Zero, Vec3f(0, 1, 0), Vec3f(0, 0, -1));
    }
    XRenderApp& OpenSampleModelScene(const std::string& target_name, std::function<void()> tick_func)
    {
      PipelineInitializeData pipeline_data;
      pipeline_data.width = 800;
      pipeline_data.height = 600;
      pipeline_data.title = target_name;
      TestPipeline* pipeline = new TestPipeline();
      pipeline_data.pipeline = pipeline;
      pipeline_data.tick_func = tick_func;
      static XRenderApp render;
      render.Initialize(pipeline_data);
      InitSetCamera(Camera::MainCamera());
      return render;
    }

    template<typename T>
    std::unique_ptr<Object> LoadSampleObject()
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh =  Res::Resources::Load<Mesh>("./obj/african_head.obj");
        std::unique_ptr<Texture2D> texture = Res::Resources::Load<Texture2D>("./obj/african_head_diffuse.tga");
        obj->SetRenderer(std::make_unique<Renderer>());
        obj->Renderer()->mesh = std::move(mesh);
        obj->Renderer()->mat = std::make_unique<Matrial>();
        obj->Renderer()->mat->shader = Shader::CreateShader<T>();
        obj->Renderer()->mat->SetAtrribute("texture", std::move(texture));
        return obj;
    }
    
}