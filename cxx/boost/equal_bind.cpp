#include <iostream>
#include <set>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/function_equal.hpp>

typedef boost::function<void (void)>  compare;

class Obj
{
public:
    Obj()
    {
    }

    void hello(void)
    {
        std::cout << "hello world" << std::endl;
    }

    bool operator==(const Obj& b)
    {
        return true;
    }
};

int main()
{
    Obj   A;
    compare  arg1(boost::bind(&Obj::hello, &A));
    compare  arg2(boost::bind(&Obj::hello, &A));
    std::set<compare>      fset;
    //fset.insert(arg1);
    //fset.insert(arg2);

    //if (boost::function_equal(arg1, arg2))
    if (true/*arg1==arg2*/)
    {
        std::cout << "equal bind" << std::endl;
    }
    else
    {
        std::cout << "not equal bind" << std::endl;
    }
    return 0;
}
