#include "Object.h"
#include "./resources/Resources.h"

XRender::Object::Object(){
}

XRender::Object::~Object()
{
}

void XRender::Object::SetPosition(const Vec3f &position)
{
    this->position = position;
    UpdateRendererMatrix();
}

const Vec3f& XRender::Object::GetPosition() const
{
    return position;
}

void XRender::Object::SetRotation(const Vec3f &rotation)
{
    this->rotation = rotation;
}

const Vec3f& XRender::Object::GetRotation() const
{
    return rotation;
}

void XRender::Object::SetScale(const Vec3f &scale)
{
    this->scale = scale;
}

const Vec3f& XRender::Object::GetScale() const
{
    return scale;
}

void XRender::Object::UpdateRendererMatrix()
{
    if(this->renderer == nullptr) return;
    worldMatrix = Math::ModelMatrix(position, scale, rotation);
    this->renderer->UpdateMatrix(worldMatrix);
}