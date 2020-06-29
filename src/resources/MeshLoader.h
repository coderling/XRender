#pragma once

#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <vector>


#include "ILoader.h"
#include "../Mesh.h"

namespace XRender::Res
{
    template<>
    class ILoader<Mesh>
    {
    public:
        ILoader();

        std::unique_ptr<Mesh> Load(const std::string& path);

        void Unload(std::unique_ptr<Mesh> res);
    private:
        void ObjFileLoad(Mesh* mesh, const std::string& path);
    private:
        std::unordered_map<std::string, std::function<void(Mesh*, const std::string&)>> meshLoaders;
    };
}