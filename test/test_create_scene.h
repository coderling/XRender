#include "Pipeline.h"
#include "test_color_shader.h"

namespace XRender::Test
{
    void ConfigSceneLight(Scene* scene)
    {
        const auto light = scene->GetLight(0);
        light->LightColor(CColor::RED);
        light->Intensity(1);
        light->SetLightType(Lighting::LightType::Directional);
        light->Position(Vec3f(0, 0, -1));
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
        std::vector<uint32_t> indeies = {2, 1, 0};

        mesh->SetPositions(points);
        mesh->SetColors(colors);
        mesh->SetIndeies(indeies);
        obj->SetRenderer(std::make_unique<Renderer>());
        obj->Renderer()->mesh = std::move(mesh);
        obj->Renderer()->mat = std::make_unique<Matrial>();
        obj->Renderer()->mat->shader = Shader::CreateShader<ColorShader>();
        obj->Transform().SetPosition(Vec3f(0, 0, -1));
        obj->Transform().SetRotation(Vec3f(0, 0, 0));
        obj->Transform().SetScale(Vec3f(1, 1, 1));
        return obj;
    }

        
}