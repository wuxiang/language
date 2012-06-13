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
    return 0;
}
