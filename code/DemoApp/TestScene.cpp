#include "TestScene.h"
#include "code/core/Objects/Triangle.h"
#include "code/core/primitive/Vertex.h"
#include "code/core/Render/Material.h"
#include "code/app/XApp.h"
#include "code/core/math/Quaternion.h"
#include "code/core/Objects/Cube.h"

static void AddTriangle()
{
    //new a triangle
    Vertex v1, v2, v3;
    v1.pos = Vector3(1, 0, 0);
    v1.color = Color(255, 0, 0, 255);
    v1.uv.u = v1.uv.v = 0;

    v2.pos = Vector3(-1, 0, 0);
    v2.color = Color(0, 255, 0, 255);
    v2.uv.u = 0; v2.uv.v = 1;

    v3.pos = Vector3(0, -1, 0);
    v3.color = Color(0, 0, 255, 255);
    v3.uv.u = 1, v3.uv.v = 0.5;

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


static void AddCube()
{
    Cube* cubeMesh = new Cube(2, 2, 2);
    auto verteies = cubeMesh->GetVerteies();
    

    Material mat;
    Object *ob = new Object();
    ob->AttachMesh(cubeMesh);
    ob->m_rotation.y = 0;
    pAppInstance->AddObject(ob);
}



void TestScene::Start()
{
    //AddTriangle();
    AddCube();
}

void TestScene::Destory()
{
 
}