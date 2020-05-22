#pragma once
#include <geometry.h>

#include "Mesh.h"
#include "Renderer.h"

class Object
{
private:
    Matrix worldMatrix;
    Mesh* mesh;
    Renderer* renderer;
};