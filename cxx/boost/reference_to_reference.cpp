#include <iostream>
#include <vector>

void fire(const int& v)
{
    std::vector<int&> vec;
    std::cout << "fire" << std::endl;
}

int main()
{
    int a = 10;
    int&  b = a;
    fire(b);
    return 0;
}
