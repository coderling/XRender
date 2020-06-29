#pragma once

#include <string>
#include <typeindex>
#include <typeinfo>
#include <memory>

#include "IO.h"

namespace XRender::Res
{
    template <class T>
    class ILoader
    {
    public:
        std::unique_ptr<T> Load(const std::string& path)
        {
             throw "loader ot type: " + typeid(T).name() + " is not implementation!";
        }

        void Unload(std::unique_ptr<T> res)
        {
             throw "loader ot type: " + typeid(T).name() + " is not implementation!";
        }

    };
}