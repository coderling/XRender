#include <tuple>
#include <type_traits>
#include <iostream>
#include <string>
#include <any>
#include <map>

#include "../thirdParty/include/geometry.h"

    #define REGISTER_UNIFORM(T, field_name)\
        auto field_address = static_cast<T BaseStruct::*>(&std::remove_pointer<decltype(this)>::type::field_name);\
        uniforms.insert_or_assign(#field_name, field_address)\

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
        REGISTER_UNIFORM(Vec3f, vec);
    }

    Vec3f vec;
};

int main()
{
    FiledStruct ft;
    ft.vec.x = 1;
    ft.vec.y = 2;
    ft.vec.z = 3;
    ft.SetUniform("vec", Vec3f(2, 2, 2));

    auto iter = ft.uniforms.find("vec");
    if(iter != ft.uniforms.end())
    {
        auto field_address = std::any_cast<Vec3f BaseStruct::*>(iter->second);
        std::cout << ft.*(field_address) << std::endl;
    }
}