#pragma once
#include <functional>

#include "Pipeline.h"

class XRender
{
public:
    XRender();
    ~XRender();
    void Initialize(Pipeline& pipeline, std::function<void()> const &tick);
    void Loop();
    void Exit();

private:
    std::function<void()> tickFunc;
    bool quit;
    Pipeline *pPipeline;
};