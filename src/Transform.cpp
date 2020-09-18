#pragma once

#include "Transform.h"
#include "math/Math.h"

XRender::Transform::Transform():position(Vec3f_Zero), rotation(Vec3f_Zero), scale(Vec3f_One)
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

const Vec3f XRender::Transform::Up() const
{  
    static Vec4f up(0, 1, 0, 0);
    up = world_matrix * up;
    return embed<3>(up);
}

const Vec3f XRender::Transform::Forward() const
{
    static Vec4f forward(0, 0, 1, 0);
    forward = world_matrix * forward;
    return embed<3>(forward);
    return Vec3f();
}