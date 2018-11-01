#include "TestScene.h"
#include "code/core/Objects/Triangle.h"
#include "code/core/primitive/Vertex.h"
#include "code/core/Render/Material.h"
#include "code/app/XApp.h"

void TestScene::Start()
{
    //new a triangle
    Vertex v1, v2, v3;
    v1.pos = Vector3(1, 0, 0);
    v1.color = Color(255, 0, 0, 255);

    v2.pos = Vector3(-1, 0, 0);
    v2.color = Color(0, 255, 0, 255);

    v3.pos = Vector3(0, 1, 0);
    v3.color = Color(0, 0, 255, 255);

    Triangle *triangleMesh = new Triangle(v1, v2, v3);

    //metrail
    Material mat;
    Shader shader;
    mat.SetShader(shader);
    const Shader *th = mat.GetShader();

    triangleMesh->SetMat(mat);

    //ob
    Object *ob = new Object();
    ob->AttachMesh(triangleMesh);
    auto tm = ob->GetMesh();

    //add ob to app;
    pAppInstance->AddObject(ob);
}