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
            std::string msg;
            msg.append("loader of type: ");
            msg.append(typeid(T).name());
            msg.append("is not implementation");
             throw msg;
        }

        void Unload(std::unique_ptr<T> res)
        {
            std::string msg;
            msg.append("loader of type: ");
            msg.append(typeid(T).name());
            msg.append("is not implementation");
             throw msg;
        }

    };
}