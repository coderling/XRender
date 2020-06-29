
#include <functional>
#include <iostream>
#include <map>
#include <any>
#include <cstring>
#include "../thirdParty/geometry.h"

struct Test
{
public:
    float pos = 10.0f;
    float* const POSITION = &pos;
};

#define BIND_ST(d, key, va, T)\
({\
auto tkey = key;\
d.insert_or_assign(key, va);\
});\
})

#define TestDic(d, key, T)\
({\
std::any res = T();\
auto it = d.find(key);\
if(it != d.end()) res = it->second;\
std::any_cast<T>(res);\
})


int main()
{
    std::any d = Vec4f();
    auto e = std::any_cast<Vec4f>(d);
    std::cout << e[0] << std::endl;
    std::map<int, std::any> dic;
    auto f = [&dic](const int& key){return std::any_cast<Vec3f>(dic[key]);};
    return 0;
}