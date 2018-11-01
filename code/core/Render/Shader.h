/*
 * File: Shader.h
 * File Created: Sunday, 21st October 2018 10:00:35 pm
 * Author: coderling (coderling@gmail.com)
 */

#pragma once

#include "code/core/math/Matrix4x3.h"
#include "code/core/primitive/Vertex.h"

struct VertInput
{
public:
    Vector3 pos;
    Color color;
};

struct VertOut
{
public:
    Vector3 pos;
    Color color;
};

class Shader
{
public:
    static void PreVert(const Matrix4x3& modelMat, const Matrix4x3& vpMat);
    virtual VertOut Vert(const VertInput& in) const;
    virtual Color Frag(const VertOut& in) const;
    static Matrix4x3 m_mvp;
};