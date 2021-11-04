#include <iostream>

import test_module;

int main()
{
    int a = 5, b = 1;
    std::cout << "a: " << a << ", b: " << b << std::endl;
    sum(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
    double_minus(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
}