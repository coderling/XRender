#pragma once
#include <vector>
#include "code/core/basic/Behavior.h"
#include "code/core/basic/Object.h" 

class TestScene
{
public:
    TestScene()
    {
    }
    void Start();
    void Destory();
private:
    std::vector<Object> m_Objects;
};