#pragma once

#include <string>
#include <Platform.h>
#include <Pipeline.h>

#include "test_pipeline.h"

namespace XRender::Test 
{
    void InitSetCamera(Camera& camera)
    {
        camera.SetPerspective(60.f, 0.1f, 1000.f);
        camera.LookAt(Vec3f_Zero, Vec3f(0, 1, 0), Vec3f(0, 0, -1));
    }
    XRender& OpenSampleModelScene(const std::string& target_name)
    {
      PipelineInitializeData pipeline_data;
      pipeline_data.width = 800;
      pipeline_data.height = 600;
      TestPipeline* pipeline = new TestPipeline();;
      InitSetCamera(Camera::MainCamera());
      pipeline_data.pipeline = pipeline;
      pipeline_data.tick_func = []() {
        std::cout << "on test tick" << std::endl;
      };
      pipeline_data.render_target = CreateRenderTarget(target_name);
      static XRender render;
      render.Initialize(pipeline_data);
      return render;
    }

    template<typename T>
    std::unique_ptr<Object> LoadSampleObject()
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh =  Res::Resources::Load<Mesh>("./obj/african_head.obj");
        std::unique_ptr<Texture2D> texture = Res::Resources::Load<Texture2D>("./obj/african_head_diffuse.tga");
        obj->renderer = std::make_unique<Renderer>();
        obj->renderer->mesh = std::move(mesh);
        obj->renderer->mat = std::make_unique<Matrial>();
        obj->renderer->mat->shader = Shader::CreateShader<T>();
        obj->renderer->mat->SetAtrribute("texture", std::move(texture));
        return obj;
    }
    
}