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

void XRender::XRender::Initialize(const PipelineInitializeData& pipeline_data)
{
    assert(pipeline_data.pipeline != nullptr);
    assert(pipeline_data.render_target != nullptr);
    assert(pipeline_data.render_target->GetWidth() > 0 && pipeline_data.render_target->GetHeight() > 0);
    tick_func = pipeline_data.tick_func;
    if(tick_func == nullptr)
    {
        tick_func = [](){};
    }

    pPipeline = pipeline_data.pipeline;
    Graphics::VirtualGraphic().InitRenderContext(pipeline_data.render_target->GetWidth(), pipeline_data.render_target->GetHeight());
    Camera::MainCamera().SetRenderTarget(pipeline_data.render_target);
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