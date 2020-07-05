#pragma once
#include <string>
#include <typeindex>
#include <typeinfo>
#include <any>
#include <unordered_map>
#include <memory>

#include "IResource.h"
#include "ILoader.h"

namespace XRender::Res
{
    class Resources
    {
    private:
    public:
        template<class T>
        static std::unique_ptr<T> Load(const std::string& path)
        {
            ILoader<T>* loader = GetOrCreateLoader<T>();

            return loader->Load(path);
        }

        template<class T>
        static void UnLoad(std::unique_ptr<T> res)
        {
            ILoader<T>* loader = GetOrCreateLoader<T>();
            loader->UnLoad(std::move(res));
        }
    private:
        template<class T>
        static ILoader<T>* GetOrCreateLoader()
        {
            std::type_index type_index = std::type_index(typeid(T));
            auto iter = loaders.find(type_index);
            ILoader<T>* loader = nullptr;
            if(iter != loaders.end())
            {
                loader = std::any_cast<ILoader<T>*>(iter->second);
            }
            else
            {
                loader = new ILoader<T>();
                loaders.emplace(type_index, loader);
            }
            return loader;
        }
        
        static std::unordered_map<std::type_index, std::any> loaders;
    };
}