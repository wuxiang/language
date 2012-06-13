#include <iostream>
#include <vector>

int main()
{
    std::vector<int>  vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    auto it = vec.begin();
    while (it != vec.end())
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::cout << "+++++++++++++++++2++++++++++++++++" << std::endl;
    std::vector<int>  other{0,1,2,3,4,5};

    for (auto &i:other)
    {
        std::cout << i << " ";
    }
    std::cout << '\n';

    return 0;
}
