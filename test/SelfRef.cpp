#include <tuple>
#include <type_traits>
#include <iostream>
#include <string>
#include <any>
#include <map>


template<class T>
void Test(const int& t, T&& value)
{
    std::cout<< t << " " << value << std::endl;
}

int main()
{
    Test(1, 1);
    const int x = 0;
    Test<int>(2, x);
}