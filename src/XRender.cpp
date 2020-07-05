#include "XRender.h"
#include "Graphics.h"

XRender::XRender::XRender()
{
    quit = false;
    tick_func = nullptr;
    pPipeline = nullptr;
}

XRender::XRender::~XRender()
{
    if(tick_func != nullptr)
    {
        tick_func = nullptr;
    }

    if(pPipeline != nullptr)
    {
        pPipeline = nullptr;
    }
}

void XRender::XRender::Initialize(PipelineInitializeData& pipeline_data)
{
    assert(pipeline_data.pipeline != nullptr);
    assert(pipeline_data.render_target != nullptr);
    assert(pipeline_data.width > 0 && pipeline_data.height > 0);

    pipeline_data.render_target->Init(pipeline_data.width, pipeline_data.height);
    tick_func = pipeline_data.tick_func;
    if(tick_func == nullptr)
    {
        tick_func = [](){};
    }

    pPipeline = pipeline_data.pipeline;
    Graphics::VirtualGraphic().InitRenderContext(pipeline_data.render_target->GetWidth(), pipeline_data.render_target->GetHeight());
    Camera::MainCamera().SetRenderTarget(std::move(pipeline_data.render_target));
}

void XRender::XRender::Loop()
{
    while (!quit)
    {
        tick_func();
        Camera::MainCamera().Update();
        pPipeline->Render();
        Graphics::VirtualGraphic().Execute();
        Camera::MainCamera().Present();
    }
}

void XRender::XRender::Exit()
{
    quit = true;
}