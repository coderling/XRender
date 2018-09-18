#pragma once
#include <vector>
#include "code/core/basic/Behavior.h"
#include "code/core/Object/Object.h"

class TestScene : public Behavior
{
public:
    TestScene()
    {
        InitScenes();
    }
private:
    std::vector<Object> m_Objects;

    void InitScenes();
};