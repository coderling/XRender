#include "Object.h"
#include "./resources/Resources.h"

XRender::Object::Object()
{
}

XRender::Object::~Object()
{
}
    
    
void XRender::Object::SetRenderer(std::unique_ptr<XRender::Renderer> renderer)
{
    this->renderer = std::move(renderer);
    this->renderer->SetMatrix(&this->transform.WorldMatrix());
}

XRender::Renderer* XRender::Object::Renderer()
{
    return renderer.get();
}
    
XRender::Transform& XRender::Object::Transform()
{
    return transform;
}