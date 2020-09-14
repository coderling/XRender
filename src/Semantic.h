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

namespace XRender
{
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
        std::unordered_map<SEMANTIC, std::vector<float>> data;
        void clear()
        {
            data.clear();
        }
    };

    struct VertexInput
    {
    public:
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
    };
    
    typedef std::unordered_map<SEMANTIC, std::function<void(VertexOutput& out, VertexOutput* triangle[], const SEMANTIC& semantic, const Vec3f& barycentric)>> barycentrix_interpolation_map_type;
    typedef std::unordered_map<SEMANTIC, std::function<void(VertexOutput& out, const SEMANTIC& semantic, VertexOutput& v1, VertexOutput& v2, const float& t)>> linear_interpolation_map_type;

    #define FILL_SHADER_STRUCT(the_struct, semantic, value)\
    {\
	    uint32_t size = std::is_same_v<std::decay_t<decltype(value)>, float> ? 1 : value.size();\
		auto iter = the_struct.data.data.find(semantic);\
		if (iter == the_struct.data.data.end())\
		{\
		    auto ret = the_struct.data.data.emplace(semantic, std::vector<float>(size));\
		    iter = ret.first;\
		}\
		for (uint32_t index = 0; index < size; ++index)\
		{\
		    iter->second[index] = value[index];\
		}\
        the_struct.data.semantics |= 1 << static_cast<uint32_t>(semantic);\
    }

    #define GET_DATA_BY_SEMATIC(ret, the_struct, semantic)\
    {\
        const auto& it = the_struct.data.data.find(semantic);\
        if(it != the_struct.data.data.end())\
        {\
	        uint32_t size = std::is_same_v<std::decay_t<decltype(ret)>, float> ? 1 : ret.size();\
            assert(size <= it->second.size());\
            for(uint32_t index = 0; index < size; ++index)\
            {\
                ret[index] = it->second[index];\
            }\
        }\
	}

    #define BIND_VERTEXINPUT_SEMANTIC(semantic)\
    this->vertex_intput_semantic |= 1 << static_cast<uint32_t>(semantic);

    #define BIND_VERTEXOUTPUT_SEMANTIC(semantic, T)\
    {\
    static_assert(SEMANTIC::SV_POSITION != semantic || std::is_same_v<T, Vec4f>);\
    static_assert(std::is_same_v<T, Vec4f>\
                  ||std::is_same_v<T, Vec3f>\
                  || std::is_same_v<T, Vec2f>\
                  || std::is_same_v<T, float>\
                  || std::is_same_v<T, Color>);\
    assert(!this->HasVertexOutputSemantic(semantic));\
    this->vertex_output_semantic |= 1 << static_cast<uint32_t>(semantic);\
    this->propertory_interpolation_funcs.emplace(semantic,\
    [](VertexOutput& out, VertexOutput* triangle[], const SEMANTIC& tsemantic, const Vec3f& barycentric)\
        {\
            T property1; GET_DATA_BY_SEMATIC(property1, (*(triangle[0])), tsemantic);\
            T property2; GET_DATA_BY_SEMATIC(property2, (*(triangle[1])), tsemantic);\
            T property3; GET_DATA_BY_SEMATIC(property3, (*(triangle[2])), tsemantic);\
            T ret = Math::BarycentricInterpolation<T>(property1, property2, property3, barycentric);\
            FILL_SHADER_STRUCT(out, tsemantic, ret);\
        }\
    );\
    this->propertory_interpolation_linear_funcs.emplace(semantic,\
    [](VertexOutput& out, const SEMANTIC& tsemantic, VertexOutput& v1, VertexOutput& v2, const float& t)\
        {\
            T property1; GET_DATA_BY_SEMATIC(property1, v1, tsemantic);\
            T property2; GET_DATA_BY_SEMATIC(property2, v2, tsemantic);\
            T& ret = Math::LinearInterpolation<T>(property1, property2, t);\
            FILL_SHADER_STRUCT(out, tsemantic, ret);\
        }\
    );\
    }


    void BarycentrixInterpolationVertex(VertexOutput& out, VertexOutput* triangle[], const Vec3f& barycentric);
    void LinearInterpolationVertex(VertexOutput& out, VertexOutput& v1, VertexOutput& v2, const float& t);
}