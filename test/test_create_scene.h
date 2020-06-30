#include "Pipeline.h"
#include "test_color_shader.h"

namespace XRender::Test
{
    void LoadObjModelAsObject(Scene* scene)
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh =  Res::Resources::Load<Mesh>("./obj/african_head.obj");
        obj->renderer = std::make_unique<Renderer>();
        obj->renderer->mesh = std::move(mesh);
        obj->renderer->mat = std::make_unique<Matrial>();
        obj->renderer->mat->shader = Shader::CreateShader<ColorShader>();
        scene->AddObject(std::move(obj));
    }

}