#include <iostream>

#include "Pipeline.h"

XRender::Pipeline::Pipeline() 
{
    scene = std::make_unique<Scene>();
}

XRender::Pipeline::~Pipeline(){}

void XRender::Pipeline::PreRender(){}

void XRender::Pipeline::Render()
{
    std::cout << "On Pipeline Render" << std::endl;
    // cull 
    // drawRenders
}

void XRender::Pipeline::DrawRenderers(const std::vector<Renderer*>& renderers)
{
    for(auto renderer : renderers)
    {
        if(renderer->geometryDirty)
        {
            renderer->Batch();
            renderer->geometryDirty = false;
        }
    }
}

void XRender::Pipeline::PostRender(){}

