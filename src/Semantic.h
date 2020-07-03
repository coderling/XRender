#pragma once
#include <stdint.h>
#include <any>
#include <map>
#include <functional>
#include <cassert>

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

    struct VertexInput
    {
    public:
        std::map<SEMANTIC, std::any> data;
    };

    struct VertexOutput
    {
    public:
        float x;
        float y;
        std::map<SEMANTIC, std::any> data;
    };


    #define FILL_SHADER_STRUCT(the_struct, semantic, value)\
    the_struct.data.insert_or_assign(semantic, value)

    #define GET_DATA_BY_SEMATIC(ret, the_struct, semantic, T)\
    {\
    auto it = the_struct.data.find(semantic);\
    if(it != the_struct.data.end()) ret = std::any_cast<T>(it->second);\
	}

    #define BIND_VERTEXINPUT_SEMANTIC(semantic)\
    this->vertex_intput_semantic |= 1 << static_cast<uint32_t>(semantic);

    #define BIND_VERTEXOUTPUT_SEMANTIC(semantic, T)\
    {\
    this->vertex_output_semantic |= 1 << static_cast<uint32_t>(semantic);\
    this->propertory_interpolation_funcs.insert_or_assign(semantic,\
    [](VertexOutput& out, VertexOutput* triangle[], const SEMANTIC& tsemantic, const Vec3f& barycentric)\
        {\
            T property1; GET_DATA_BY_SEMATIC(property1, (*(triangle[0])), tsemantic, T);\
            T property2; GET_DATA_BY_SEMATIC(property2, (*(triangle[1])), tsemantic, T);\
            T property3; GET_DATA_BY_SEMATIC(property3, (*(triangle[2])), tsemantic, T);\
            T ret = Math::BarycentricInterpolation<T>(property1, property2, property3, barycentric);\
            FILL_SHADER_STRUCT(out, tsemantic, ret);\
        }\
    );\
    }
}