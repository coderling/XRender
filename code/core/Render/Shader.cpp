/*
 * File: Shader.cpp
 * File Created: Sunday, 21st October 2018 10:00:44 pm
 * Author: coderling (coderling@gmail.com)
 */

#include "Shader.h"

Matrix4x3 Shader::m_mvp;

void Shader::PreVert(const Matrix4x3& modelMat, const Matrix4x3& vpMat)
{
    m_mvp = modelMat * vpMat;
}

VertOut Shader::Vert(const VertInput& in) const
{
    VertOut out;
    out.pos = in.pos * m_mvp;
    out.color = in.color;
    return out;
}

Color Shader::Frag(const VertOut& in) const
{
    Color fc = in.color;
    return fc;
}