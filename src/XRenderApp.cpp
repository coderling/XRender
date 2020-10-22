#include "XRenderApp.h"
#include "Graphics.h"
#include "XTime.h"
#include "ShadowMap.h"
#include "RenderTexture.h"
#include "GraphicsEnum.h"
#include "RenderDevice.h"

XRender::XRenderApp::XRenderApp()
{
    quit = false;
    pPipeline = nullptr;
}

XRender::XRenderApp::~XRenderApp()
{
    ticks.clear();
    if(pPipeline != nullptr)
    {
        pPipeline = nullptr;
    }
}

void XRender::XRenderApp::Initialize(PipelineInitializeData& pipeline_data)
{
    assert(pipeline_data.pipeline != nullptr);
    assert(pipeline_data.width > 0 && pipeline_data.height > 0);

    RegistrTickFunc(pipeline_data.tick_func);
    pPipeline = pipeline_data.pipeline;

    Graphics::VirtualGraphic().SetupGraphics(pipeline_data.width, pipeline_data.height, pipeline_data.title);
    Camera::MainCamera().SetViewPort(0, 0, 1, 1);
    RegisterCamera(&Camera::MainCamera());
    Lighting::ShadowMap::Setup(pPipeline);
}

void XRender::XRenderApp::Loop()
{
    while (!quit)
    {
        XTime::Time().Update();
        InnerTick();
        pPipeline->BaseRender(cameras);
        std::cout << "FPS:" << XTime::Time().Fps() << std::endl;
    }
}

void XRender::XRenderApp::TickCamera() const
{
    for(auto& c : cameras)
    {
        c->Update();
    }
}

void XRender::XRenderApp::RegisterCamera(Camera* camera)
{
    for(const auto& c : cameras)
    {
        if(c == camera)
        {
            return;
        }
    }

    cameras.emplace_back(camera);
}

void XRender::XRenderApp::UnRegisterCamera(Camera* camera)
{
    auto iter = cameras.begin();
    for(; iter != cameras.end(); iter++)
    {
        if(*iter == camera)
        {
            cameras.erase(iter);
            return;
        }
    }
}

void XRender::XRenderApp::RegistrTickFunc(std::function<void()> tick)
{
    for(auto& t : ticks)
    {
        if(t.target<void()>() == tick.target<void()>())
        {
            return;
        }
    }
    ticks.emplace_back(tick);
}

void XRender::XRenderApp::UnRegistrTickFunc(std::function<void ()> tick)
{
    auto iter = ticks.begin();
    for(; iter != ticks.end(); iter++)
    {
        if(*iter->target<void()>() == tick.target<void()>())
        {
            ticks.erase(iter);
            return;
        }
    }
}

void XRender::XRenderApp::InnerTick()
{
    RenderDevice::Device()->OnUpdate();
    TickCamera();
    for(auto& tick : ticks)
    {
        tick();
    }
}

void XRender::XRenderApp::Exit()
{
    quit = true;
}

XRender::Pipeline* XRender::XRenderApp::GetPipeline() const
{
    return pPipeline;
}