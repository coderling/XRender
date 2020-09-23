#pragma once
#include <stdint.h>
#include <any>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <cassert>
#include <typeindex>
#include <typeinfo>
#include <type_traits>

#include "math/Math.h"
#include "Color.h"

namespace XRender
{
    template <typename T, typename U>
    struct decay_equiv : 
        std::is_same<typename std::decay<T>::type, U>::type 
    {};

    enum struct SEMANTIC: uint32_t
    {
        POSITION = 0,
        COLOR = 1,
        NORMAL = 2,
        UV0 = 3,
        UV1 = 4,
        UV2 = 5,
        UV3 = 6,
        SV_POSITION = 7,
        SV_TARGET = 8,
        MAX
    };
    
    struct VertexData
    {
    public:
        uint32_t semantics = 0;
        std::unordered_map<SEMANTIC, Vec4f> data;
    public:
        void clear()
        {
            data.clear();
        }

        template<class T>
        const T Get(const SEMANTIC& semantic) const{
            //static_assert(SEMANTIC::SV_POSITION != semantic || std::is_same_v<T, Vec4f>);
            static_assert(std::is_same_v<std::decay<T>::type, Vec4f>
                  ||std::is_same_v<std::decay<T>::type, Vec3f>
                  || std::is_same_v<std::decay<T>::type, Vec2f>
                  || std::is_same_v<std::decay<T>::type, float>
                  || std::is_same_v<std::decay<T>::type, Color>);
            T ret;
            const auto& it = data.find(semantic);
            if(it != data.end())
            {
                uint32_t size = std::is_same_v<T, float> ? 1 : std::decay<T>::type::size();
                assert(size <= it->second.size());
                for(uint32_t index = 0; index < size; ++index)
                {
                    ret[index] = it->second[index];
                }
            }

            return ret;
        }

        template<class T>
        void Set(const SEMANTIC& semantic, T&& value){
            //static_assert(SEMANTIC::SV_POSITION != semantic || std::is_same_v<T, Vec4f>);
            static_assert(std::is_same_v<std::decay<T>::type, Vec4f>
                  ||std::is_same_v<std::decay<T>::type, Vec3f>
                  || std::is_same_v<std::decay<T>::type, Vec2f>
                  || std::is_same_v<std::decay<T>::type, float>
                  || std::is_same_v<std::decay<T>::type, Color>);
            uint32_t size = std::is_same_v<T, float> ? 1 : std::decay<T>::type::size();
	    	auto iter = data.find(semantic);
	    	if (iter == data.end())
	    	{
	    	    auto ret = data.emplace(semantic, Vec4f());
	    	    iter = ret.first;
	    	}
	    	for (uint32_t index = 0; index < size; ++index)
	    	{
	    	    iter->second[index] = value[index];
	    	}
            semantics |= 1 << static_cast<uint32_t>(semantic);
           }
    };

    struct VertexInput
    {
    public:
        template<class T>
        const T Get(const SEMANTIC& semantic) const
        {
            return data.Get<T>(semantic);
        }
        template<class T>
        void Set(const SEMANTIC& semantic, T&& value)
        {
            data.Set<T>(semantic, std::forward<T>(value));
        }
    
        VertexData data;
    };

    struct VertexOutput
    {
    public:
        Vec2f screen;
        float viewDepth;
        float viewZ;
        Vec4f point;
        VertexData data;
        
        template<class T>
        const T Get(const SEMANTIC& semantic) const{
            return data.Get<T>(semantic);
        }
        template<class T>
        void Set(const SEMANTIC& semantic, T&& value){
            data.Set<T>(semantic, std::forward<T>(value));
        }
    };
    
    typedef std::unordered_map<SEMANTIC, std::function<void(VertexOutput& out, VertexOutput* triangle[], const SEMANTIC& semantic, const Vec3f& barycentric)>> barycentrix_interpolation_map_type;
    typedef std::unordered_map<SEMANTIC, std::function<void(VertexOutput& out, const SEMANTIC& semantic, VertexOutput& v1, VertexOutput& v2, const float& t)>> linear_interpolation_map_type;
    void BarycentrixInterpolationVertex(VertexOutput& out, VertexOutput* triangle[], const Vec3f& barycentric);
    void LinearInterpolationVertex(VertexOutput& out, VertexOutput& v1, VertexOutput& v2, const float& t);
}