#include "code/core/Object/Cube.h"
#include "code/core/basic/Camera.h"
#include <iostream>


void TestCameraAPI()
{
    Camera ca;
    ca.Init(800, 600, Vector3(0, 0, -50), Vector3(0, 1, 0), Vector3(0, 0, 1));

    Vector3 vec(0, 28.6, 0);
    Vector3 afTr = vec * ca.GetCameraMatrix();
    std::cout << " afTr:" + afTr.ToString() << std::endl;
    Vector3 proVec = afTr * ca.GetProjectMatrix();
    std::cout << " proVec:" + proVec.ToString() << std::endl;
    Vector3 tPro = vec * ca.GetVPMatrix();
    std::cout << "tPro:" << tPro.ToString() << std::endl;
}

void TestCubeData()
{
    std::cout << "cubeData: ---------------------" << std::endl;
    Cube cube(3, 4, 5);
    Vertex* pv = cube.GetVerteies();
    cube.m_position = Vector3(1, 1, 1);
    for(int i = 0; i < 8; i++)
    {
        Vertex tv = pv[i];
        std::cout << " " << i << " " << tv.pos.ToString() << std::endl;
        Vector3 wc = tv.pos * cube.ModelMatrix();
        std::cout << " " << i << " " << wc.ToString() << std::endl << std::endl;
    }
}

int main()
{
    TestCubeData();
    //TestCameraAPI();
    char a;
    std::cin >> a;
    return 0;
}