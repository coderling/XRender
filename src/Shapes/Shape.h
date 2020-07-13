#pragma once
#include <geometry.h>

#include "../Object.h"
#include "../Mesh.h"
#include "ShapeData.h"
#include "Capsule.h"
#include "Cube.h"
#include "Panel.h"
#include "Sphere.h"

namespace XRender::Shapes
{

    template<typename T>
    std::unique_ptr<Object> CreateShape()
    {
        const auto& data = T::GetShapeData();
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
        mesh->SetWitchShapeData(data);
        obj->renderer = std::make_unique<Renderer>();
        obj->renderer->mesh = std::move(mesh);
        return obj;
    }
}