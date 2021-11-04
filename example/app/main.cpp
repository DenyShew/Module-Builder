#include <iostream>

import server;

int main()
{
    int a = 5, b = 1;
    std::cout << "a: " << a << ", b: " << b << std::endl;
    sum(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
    minus(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
}