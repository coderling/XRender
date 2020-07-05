#pragma once

#include <unordered_map>
#include <functional>

#include "ILoader.h"
#include "../Texture2D.h"

namespace XRender::Res
{
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
