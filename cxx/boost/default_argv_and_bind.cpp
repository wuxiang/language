#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

typedef boost::function<void (const std::string&)> func;

void test(const std::string& val, const int a, const int b)
{
    std::cout << val << "=====>a + b = " << a + b << std::endl;
}

void test1(const func& f)
{
    f("hello");
}

int main()
{
    test1(boost::bind(&test, _1, 80, 8));
    return 0;
}
