#pragma once
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

#include "PostProcessEffect.h"
#include "../Camera.h"

namespace XRender
{
    class PostProcess final
    {
    public:
        template<class T>
        static PostProcessEffect* AddPostProcessEffect(Camera* camera)
        {
            PostProcess* postprocess = nullptr;
            if(camera_postprocess.count(camera) == 0)
            {
                postprocess = new PostProcess();
                camera_postprocess.emplace(camera, postprocess);
            }
            else
            {
                postprocess = camera_postprocess[camera].get();
            }

            std::type_index type_index = std::type_index(typeid(T));
            auto effect = postprocess->GetPostProcessEffect<T>();
            if (effect == nullptr)
            {
				effect = new T();
				postprocess->effects.emplace(type_index, effect);
            }
            return effect;
        }

        template<class T>
        static PostProcessEffect* GetPostProcessEffect(Camera* camera)
        {
            auto postprocess = GetPostProcess(camera);
            return postprocess->GetPostProcessEffect<T>();
        }
        
        static PostProcess* GetPostProcess(Camera* camera)
        {

            if(camera_postprocess.count(camera) != 0)
                return camera_postprocess[camera].get();
            
            return nullptr;
        }
        
        template<class T>
        PostProcessEffect* GetPostProcessEffect()
        {
            std::type_index type_index = std::type_index(typeid(T));
            if(effects.count(type_index) != 0)
                return effects[type_index].get();

            return nullptr;
        }

        static void ExecutePostProcess(Camera* camera);
    private:
        static std::unordered_map<Camera*, std::unique_ptr<PostProcess>> camera_postprocess;

    private:
        std::unordered_map<std::type_index, std::unique_ptr<PostProcessEffect>> effects;
    };
}