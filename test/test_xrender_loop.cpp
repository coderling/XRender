#include <iostream>

#include "test_util.h"

int main(int argc, char**argv)
{
    auto& render = XRender::Test::OpenSampleModelScene<XRender::Test::DiffuseColor>("Diffuse");
    render.Loop();
    return 0;
}