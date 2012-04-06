#include <iostream>

struct Empty
{
};

class Ety
{
};

int main()
{
    std::cout << sizeof(struct Empty) << std::endl;
    return 0;
}
