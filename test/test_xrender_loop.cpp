#include <iostream>

#include "test_pipeline.h"
#include "test_create_scene.h"
#include "Platform.h"

int main(int argc, char**argv)
{
    XRender::PipelineInitializeData pipeline_data;
    XRender::Test::TestPipeline pipeline;
    XRender::Test::LoadObjModelAsObject(pipeline.scene.get());
    XRender::ImageRenderTarget render_context;
    pipeline_data.pipeline = &pipeline;
    pipeline_data.tick_func = [](){
        std::cout<< "on test tick" << std::endl;
    };
    pipeline_data.render_target = &render_context;
    XRender::XRender render;
    render.Initialize(pipeline_data);
    render.Loop();
    return 0;
}