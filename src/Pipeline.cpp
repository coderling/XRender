#include <iostream>

#include "Pipeline.h"
#include "Graphics.h"
#include "ShadowMap.h"
#include "PostProcess/PostProcess.h"

XRender::Pipeline::Pipeline() 
{
    scene = std::make_unique<Scene>();
}

XRender::Pipeline::~Pipeline()
{
    Lighting::ShadowMap::Release();
}

void XRender::Pipeline::Prepare()
{ }

void XRender::Pipeline::PreRender(Camera* camera){}

void XRender::Pipeline::Render(Camera* camera)
{
    std::cout << "On Pipeline Render" << std::endl;
    // cull 
    // drawRenders
}

void XRender::Pipeline::BaseRender(const std::vector<Camera*>& cameras)
{
    for(const auto& camera : cameras)
    {
        PreRender(camera);
        Render(camera);
        PostRender(camera);
        PostProcess::ExecutePostProcess(camera);
        camera->Present();
    }
}

void XRender::Pipeline::DrawRenderers(const std::vector<Renderer*>& renderers, Camera* camera)
{
    for(auto renderer : renderers)
    {
        if(renderer->geometryDirty)
        {
            renderer->Batch();
            renderer->geometryDirty = false;
        }
        Graphics::VirtualGraphic().ActiveRender(renderer->GetVbo());
    }

    Graphics::VirtualGraphic().BeginFrame();
    Lighting::ShadowMap::Render(camera);
    camera->SyncGraphicsCameraData();
    Graphics::VirtualGraphic().Execute();
    Graphics::VirtualGraphic().EndFrame();
}

void XRender::Pipeline::PostRender(Camera* camera){}

