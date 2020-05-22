# include "XRender.h"

XRender::XRender()
{
    quit = false;
    tickFunc = nullptr;
    pPipeline = nullptr;
}

XRender::~XRender()
{
    if(tickFunc != nullptr)
    {
        tickFunc = nullptr;
    }

    if(pPipeline != nullptr)
    {
        pPipeline = nullptr;
    }
}

void XRender::Initialize(Pipeline& pipeline, std::function<void()> const& tick)
{
    tickFunc = tick;
    pPipeline = &pipeline;
}

void XRender::Loop()
{
    while (!quit)
    {
        if(tickFunc != nullptr)
        {
            tickFunc();
        }
    
        if(pPipeline != nullptr)
        {
            pPipeline->Render();
        }
    }
}

void XRender::Exit()
{
    quit = true;
}