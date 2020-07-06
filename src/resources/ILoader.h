#pragma once

#include <string>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <functional>
#include <unordered_map>

#include "IO.h"
#include "../Mesh.h"
#include "../Texture2D.h"

namespace XRender::Res
{
    template <class T>
    class ILoader
    {
    public:
        ILoader<T>(){}

        std::unique_ptr<T> Load(const std::string& path)
        {
            std::string msg;
            msg.append("loader of type: ");
            msg.append(typeid(T).name());
            msg.append("is not implementation");
             throw msg;
        }

        void UnLoad(std::unique_ptr<T> res)
        {
            std::string msg;
            msg.append("loader of type: ");
            msg.append(typeid(T).name());
            msg.append("is not implementation");
             throw msg;
        }
    };
    
    template<>
    class ILoader<Mesh>
    {
    public:
        ILoader();

        std::unique_ptr<Mesh> Load(const std::string& path);

        void UnLoad(std::unique_ptr<Mesh> res);
    private:
        void ObjFileLoad(Mesh* mesh, const std::string& path);
    private:
        std::unordered_map<std::string, std::function<void(Mesh*, const std::string&)>> meshLoaders;
    };
    
    
    template<>
    class ILoader<Texture2D>
    {
    public:
        ILoader();

        std::unique_ptr<Texture2D> Load(const std::string& path);

        void UnLoad(std::unique_ptr<Texture2D> res);

    private:
        void TGALoad(Texture2D* texture, const std::string& path);
    private:
        std::unordered_map<std::string, std::function<void(Texture2D*, const std::string&)>> textureLoaders;
    };
}