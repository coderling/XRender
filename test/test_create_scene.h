#include "Pipeline.h"
#include "test_color_shader.h"

namespace XRender::Test
{
    void ConfigSceneLight(Scene* scene)
    {
        const auto light = scene->GetLight(0);
        auto data = light->GetData();
        data->color = CColor::RED;
        data->intensity = 1;
        data->range = 0;
        data->world_pos = Vec4f(0, 0, -1, 0);
        light->Enable();
    }
    
    std::unique_ptr<Object> LoadSampleTriangleAsObject()
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
        std::vector<Vec3f> points =  {
            {-0.25, -0.25, 0},
            {-0.25, 0.25, 0},
            {0.25, 0.25, 0},
            {0.25, -0.25, 0},
        };
        std::vector<Color> colors = {
            Color(1, 0, 0, 1),
            Color(0, 1, 0, 1),
            Color(0, 0, 1, 1),
            Color(0, 1, 1, 1),
        };
        std::vector<uint32_t> indeies = {0, 1, 2};

        mesh->SetPositions(points);
        mesh->SetColors(colors);
        mesh->SetIndeies(indeies);
        obj->renderer = std::make_unique<Renderer>();
        obj->renderer->mesh = std::move(mesh);
        obj->renderer->mat = std::make_unique<Matrial>();
        obj->renderer->mat->shader = Shader::CreateShader<ColorShader>();
        obj->SetPosition(Vec3f(0, 0, -1));
        obj->SetRotation(Vec3f(0, 0, 0));
        obj->SetScale(Vec3f(1, 1, 1));
        return obj;
    }

        
}