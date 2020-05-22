#include <iostream>

#include "Pipeline.h"

Pipeline::~Pipeline(){}

void Pipeline::PreRender(){}

void Pipeline::Render()
{
    std::cout << "On Pipeline Render" << std::endl;
}

void Pipeline::PostRender(){}

