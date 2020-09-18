#include "XRender.h"
#include "Graphics.h"
#include "XTime.h"
#include "ShadowMap.h"
#include "RenderTexture.h"
#include "GraphicsEnum.h"
#include "RenderDevice.h"

XRender::XRender::XRender()
{
    quit = false;
    pPipeline = nullptr;
}

XRender::XRender::~XRender()
{
    ticks.clear();
    if(pPipeline != nullptr)
    {
        pPipeline = nullptr;
    }
}

void XRender::XRender::Initialize(PipelineInitializeData& pipeline_data)
{
    assert(pipeline_data.pipeline != nullptr);
    assert(pipeline_data.width > 0 && pipeline_data.height > 0);

    RegistrTickFunc(pipeline_data.tick_func);
    pPipeline = pipeline_data.pipeline;

    Graphics::VirtualGraphic().SetupGraphics(pipeline_data.width, pipeline_data.height, pipeline_data.title);
    Camera::MainCamera().SetViewPort(0, 0, 1, 1);
    RegisterCamera(&Camera::MainCamera());
    ShadowMap::Setup(pPipeline);
}

void XRender::XRender::Loop()
{
    while (!quit)
    {
        XTime::Time().Update();
        InnerTick();
        pPipeline->BaseRender(cameras);
        std::cout << "FPS:" << XTime::Time().Fps() << std::endl;
    }
}

void XRender::XRender::TickCamera() const
{
    for(auto& c : cameras)
    {
        c->Update();
    }
}

void XRender::XRender::RegisterCamera(Camera* camera)
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

void XRender::XRender::UnRegisterCamera(Camera* camera)
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

void XRender::XRender::RegistrTickFunc(std::function<void()> tick)
{
    for(const auto& t : ticks)
    {
        if(t.target<void()>() == tick.target<void()>())
        {
            return;
        }
    }
    ticks.emplace_back(tick);
}

void XRender::XRender::UnRegistrTickFunc(std::function<void ()> tick)
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

void XRender::XRender::InnerTick()
{
    RenderDevice::Device()->OnUpdate();
    TickCamera();
    for(const auto& tick : ticks)
    {
        tick();
    }
}

void XRender::XRender::Exit()
{
    quit = true;
}

XRender::Pipeline* XRender::XRender::GetPipeline() const
{
    return pPipeline;
}