#include <iostream>

#include "Pipeline.h"


int main(int argc, char**argv)
{
    Pipeline pipeline;
    XRender render;
    render.Initialize(pipeline, []()
    {
        std::cout<< "on test tick" << std::endl;
    });

    render.Loop();
    return 0;
}