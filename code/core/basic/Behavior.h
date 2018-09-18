/*
游戏行为
*/

#pragma once

#include "BaseObject.h"

class Behavior : public BaseObject
{
public:
    Behavior()
    {
        m_enable = false;
    }

    void Enable();
    void Disable();

    virtual void OnEnable() const;
    virtual void Update() const;
    virtual void OnDisable() const;

protected:
    bool m_enable;
};