#pragma once

#include "Transform.h"
#include "math/Math.h"

XRender::Transform::Transform():position(Vec3f_Zero), scale(Vec3f_One), rotation(Vec3f_Zero)
{

}
void XRender::Transform::SetPosition(const Vec3f& position)
{
    this->position = position;
    UpdateWorldMatrix();
}

const Vec3f& XRender::Transform::GetPosition() const
{
    return this->position;
}

void XRender::Transform::SetRotation(const Vec3f& rotation)
{
    this->rotation = rotation;
    UpdateWorldMatrix();
}

const Vec3f& XRender::Transform::GetRotation() const
{
    return this->rotation;
}

void XRender::Transform::SetScale(const Vec3f& scale)
{
    this->scale = scale;
    UpdateWorldMatrix();
}

const Vec3f& XRender::Transform::GetScale() const
{
    return this->scale;
}

const Matrix& XRender::Transform::WorldMatrix() const
{
    return world_matrix;
}

void XRender::Transform::UpdateWorldMatrix()
{
    world_matrix = Math::ModelMatrix(position, scale, rotation);
}