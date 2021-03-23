#include <string>
#include <iostream>

template<typename T> const T& condif(const T& exp1, const T& exp2, bool condition)
{
    if (condition)
        return exp1;
    else
        return exp2;
}

int main()
{
    std::string cond1("statement was true");
    std::string cond2("statement was false");
    std::cout << condif(cond1, cond2, false) << '\n';
    std::cout << condif(8, 5, true) << '\n';
    std::cout << condif(8, 7, false) << '\n';
}
