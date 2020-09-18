#include <iostream>

#include "../thirdParty/include/geometry.h"
#include "../src/math/Math.h"
#include "../src/math/Math.cpp"


int main()
{

    
    /*
    std::string dy[3][3]{
        {"Cy", "", "Sy"},
        {"", "1", ""},
        {"-Sy", "", "Cy"},
    };
    std::string dx[3][3]{
        {"1", "", ""},
        {"", "Cx", "-Sx"},
        {"", "Sx", "Cx"},
    };
    std::string dz[3][3]{
        {"Cz", "-Sz", ""},
        {"Sz", "Cz", ""},
        {"",   "", "1"},
    };
    t[0][0] = Cy * 1 + 0 * 0   + Sy * 0 = Cy
    t[0][1] = Cy * 0 + 0 * Cx  + Sy * Sx = SySx
    t[0][2] = Cy * 0 + 0 * -Sx + Sy * Cx = SyCx
    
    t[1][0] = 0 * 1 + 1 * 0    + 0 * 0 = 0
    t[1][1] = 0 * 0 + 1 * Cx   + 0 * Sx = Cx
    t[1][2] = 0 * 0 + 1 * -Sx  + 0 * Cx = -Sx
    
    t[2][0] = -Sy * 1 + 0 * 0    + Cy * 0 = -Sy
    t[2][1] = -Sy * 0 + 0 * Cx   + Cy * Sx = CySx
    t[2][2] = -Sy * 0 + 0 * -Sx  + Cy * Cx = CyCx


    t[0][0] = Cy * Cz  + SySx * Sz  + SyCx * 0 = CyCz + SySxSz
    t[0][1] = Cy * -Sz + SySx * Cz  + SyCx * 0 = -CySz + SySxCz
    t[0][2] = Cy * 0   + SySx * 0   + SyCx * 1 = SyCx
    
    t[1][0] = 0 * Cz  + cx * Sz  + -Sx * 0 = CxSz
    t[1][1] = 0 * -Sz + cx * Cz  + -Sx * 0 = CxCz
    t[1][2] = 0 * 0   + cx * 0   + -Sx * 1 = -Sx
    
    t[2][0] = -Sy * Cz  + CySx * Sz  + CyCx * 0 = -SyCz + CySxSz
    t[2][1] = -Sy * -Sz + CySx * Cz  + CyCx * 0 = SySz + CySxCz
    t[2][2] = -Sy * 0   + CySx * 0   + CyCx * 1 = CyCx
    */
    Matrix rotation = XRender::Math::RotateMatrix(Vec3f(30, 90, 30));
    std::cout << rotation << std::endl;
    Vec3f v = XRender::Math::RotateToEuler(rotation);
    std::cout << v << std::endl;
}