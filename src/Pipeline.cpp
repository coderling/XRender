#include <iostream>

#include "Pipeline.h"
#include "Graphics.h"

XRender::Pipeline::Pipeline() 
{
    scene = std::make_unique<Scene>();
}

XRender::Pipeline::~Pipeline(){}

void XRender::Pipeline::Prepare()
{ }

void XRender::Pipeline::PreRender(){}

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
        PreRender();
        Render(camera);
        PostRender();
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

    camera->SyncGraphicsCameraData();
    Graphics::VirtualGraphic().Execute();
}

void XRender::Pipeline::PostRender(){}

