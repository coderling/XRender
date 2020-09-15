#include "PostProcess.h"
#include "../Graphics.h"

std::unordered_map<XRender::Camera*, std::unique_ptr<XRender::PostProcess>> XRender::PostProcess::camera_postprocess;

void XRender::PostProcess::ExecutePostProcess(Camera *camera)
{
    static PostProcessContext context;
    context.render_context = Graphics::VirtualGraphic().GetRenderContext();
    PostProcess* process = GetPostProcess(camera);
    if (process == nullptr)
        return;

    for(const auto& kv : process->effects)
    {
        context.camera = camera;
        kv.second->Render(&context);
    }
}