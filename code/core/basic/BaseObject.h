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
private:
    static unsigned long m_idGentor;
    unsigned long m_id;
};


unsigned long BaseObject::m_idGentor = 0;