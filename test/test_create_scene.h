#include "Pipeline.h"
#include "test_color_shader.h"
#include "test_random_color_shader.h"

namespace XRender::Test
{
    void LoadObjModelAsObject(Scene* scene)
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh =  Res::Resources::Load<Mesh>("./obj/african_head.obj");
        obj->renderer = std::make_unique<Renderer>();
        obj->renderer->mesh = std::move(mesh);
        obj->renderer->mat = std::make_unique<Matrial>();
        obj->renderer->mat->shader = Shader::CreateShader<RandomColor>();
        obj->SetPosition(Vec3f(0, 0, -2));
        scene->AddObject(std::move(obj));
    }
    
    void LoadSampleTriangleAsObject(Scene* scene)
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
        std::vector<Vec3f> points =  {
            Vec3f(-0.5, 0, 0),
            Vec3f(0, 0.5, 0),
            Vec3f(0.5, 0, 0)
        };
        std::vector<Color> colors = {
            Color(1, 0, 0, 1),
            Color(0, 1, 0, 1),
            Color(0, 0, 1, 1),
        };
        std::vector<uint32_t> indeies = {0, 1, 2};

        mesh->SetPositions(points);
        mesh->SetColors(colors);
        mesh->SetIndeies(indeies);
        obj->renderer = std::make_unique<Renderer>();
        obj->renderer->mesh = std::move(mesh);
        obj->renderer->mat = std::make_unique<Matrial>();
        obj->renderer->mat->shader = Shader::CreateShader<ColorShader>();
        obj->SetPosition(Vec3f(0, 0, -2));
        scene->AddObject(std::move(obj));
    }

    void InitSetCamera(Camera& camera)
    {
        camera.SetPerspective(60.f, 0.1f, 1000.f);
        camera.LookAt(Vec3f_Zero, Vec3f(0, 1, 0), Vec3f(0, 0, -1));
    }
        
}