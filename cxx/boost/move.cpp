//#include <boost/move/move.hpp>
#include <boost/unordered_set.hpp>
#include <iostream>

int main()
{
    //std::vector<int> a(10);
    //std::vector<int> b(10);
    //boost::move(a.begin(), a.end(), b);
    boost::unordered_set<int>  a;
    boost::unordered_set<int>  b;

    for (int i = 0; i < 5; ++i)
    {
        a.insert(i);
    }

    boost::unordered_set<int>::iterator it = a.begin();
    for (; it != a.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "==========================================" << std::endl;

    b.swap(a);

    std::cout << "+++++++++++++++++a after swap++++++++++++++++++" << std::endl;
    for (it = a.begin(); it != a.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "++++++++++++++b after swap++++++++++++++++" << std::endl;

    for (it = b.begin(); it != b.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}
