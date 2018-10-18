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

    virtual ~Behavior(){}

    inline void Enable(){ 
        if(!m_enable)
        {
            m_enable = true;
            OnEnable();
        }
    }

    void Disable()
    {
        if(m_enable)
        {
            m_enable = false;
            OnDisable();
        }
    }

    virtual void OnEnable(){}
    virtual void Update(){}
    virtual void OnDisable(){}

protected:
    bool m_enable;
};