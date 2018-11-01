/*
 * File: Material.h
 * File Created: Thursday, 25th October 2018 9:51:05 pm
 * Author: coderling (coderling@gmail.com)
 */

#pragma once

#include "code/core/Render/Shader.h"
#include "code/core/basic/Mesh.h"

class Material
{
public:
    inline const Shader* GetShader(){ return &m_shader; }
    inline void SetShader(const Shader& shader) { m_shader = shader; }
private:
    Shader m_shader;    
};