#pragma once

#include <string>
#include <Platform.h>

#include "test_pipeline.h"
#include "test_create_scene.h"

namespace XRender::Test 
{
    template<typename T>
    void OpenSampleModelScene(const std::string& target_name)
    {
      PipelineInitializeData pipeline_data;
      pipeline_data.width = 800;
      pipeline_data.height = 600;
      TestPipeline pipeline;
      LoadObjModelAsObject<T>(pipeline.scene.get());
      InitSetCamera(Camera::MainCamera());
      pipeline_data.pipeline = &pipeline;
      pipeline_data.tick_func = []() {
        std::cout << "on test tick" << std::endl;
      };
      pipeline_data.render_target = CreateRenderTarget(target_name);
      XRender render;
      render.Initialize(pipeline_data);
      render.Loop();
    }
}