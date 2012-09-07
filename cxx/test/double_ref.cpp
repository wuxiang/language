#include <iostream>

int main()
{
    int a = 10;
    int& b = a;
    int& c = b;
    std::cout << "b = " << b << ", c = " << c << std::endl;

    std::cout << (0 % 1) << " " << (1 % 1) << " " << (3 % 1) << std::endl;
}
