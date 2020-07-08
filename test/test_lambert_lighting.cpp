
#include <iostream>

#include <DiffuseColor.hpp>

#include "test_util.h"

int main(int argc, char**argv)
{
    XRender::Test::OpenSampleModelScene<XRender::Shaders::DiffuseColor>("LambertLight");
    return 0;
}