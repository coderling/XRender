/*
所有场景对象和行为都继承与这个累
*/

#pragma once

class BaseObject
{
public:
    BaseObject()
    {
        m_id = ++m_idGentor;
        m_enable = false;
    }

    virtual ~BaseObject()
    {
        
    }

    inline unsigned long GetID()
    {
        return m_id;
    }

    bool operator==(BaseObject& bo)
    {
        return m_id = bo.m_id;
    }

    bool operator!=(BaseObject& bo)
    {
        return !(*this == bo);
    }

    inline void Enable()
    {
        if(!m_enable)
        {
            m_enable = true;
            OnEnable();
        }
    }

    inline void Disable()
    {
        if(m_enable)
        {
            m_enable = false;
            OnDisable();
        }
    }

    inline bool IsEnable()
    {
        return m_enable;
    }

    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;
    virtual void Start() = 0;
protected:
    bool m_enable;
private:
    unsigned long m_id;
    static unsigned long m_idGentor;
};
