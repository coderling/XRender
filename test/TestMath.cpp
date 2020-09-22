#include <iostream>

#include "../thirdParty/include/geometry.h"
#include "../src/math/Math.h"
#include "../src/math/Math.cpp"


int main()
{
    Matrix m = XRender::Math::Perspective(60, 8.0f/ 6.0f, 0.1f, 500.f);
    std::cout << m << std::endl;

    
    
}