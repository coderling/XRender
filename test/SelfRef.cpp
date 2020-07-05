#include <tuple>
#include <type_traits>
#include <iostream>
#include <string>
#include <any>
#include <map>

#include "../thirdParty/include/geometry.h"

    #define REGISTER_UNIFORM(field_name)\
        uniforms.insert_or_assign(#field_name, &::field_name)\

class BaseStruct
{
    public:
    template<typename T>
    void SetUniform(const std::string& field_name, const T& value)
    {
        const auto& iter = uniforms.find(field_name);
        if(iter != uniforms.end())
        {
            this->*(std::any_cast<T BaseStruct::*>(iter->second)) = value; 
        }
    }
    
    std::map<std::string, std::any> uniforms;
};



class FiledStruct: public BaseStruct
{
    public:
    FiledStruct(){
        auto field = &(vec);
        uniforms.insert_or_assign("vec" , (&::vec));
    }

    Vec3f vec;
};

int main()
{
    auto vec_field = &FiledStruct::vec;
}