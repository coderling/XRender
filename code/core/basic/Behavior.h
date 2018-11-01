/*
游戏行为
*/

#pragma once

#include "BaseObject.h"

class Object;

class Behavior : public BaseObject
{
    friend Object;
public:
    Behavior();
    virtual ~Behavior();

protected:
    Object* m_object;

    virtual void Update();
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void Start();
};