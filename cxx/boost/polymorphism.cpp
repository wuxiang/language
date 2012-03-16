#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

typedef boost::function<void (int)>  fun;

class A/*: public boost::enable_shared_from_this<A>*/
{
public:
    virtual void print()
    {
        std::cout << "A::print" << std::endl;
    }
};

class B
{
public:
    virtual void print1()
    {
        std::cout << "B::print1" << std::endl;
    }
};

class D
{
public:
    D(fun  callback): m_fun(callback)
    {
    }

    void world(void)
    {
        m_fun(10);
    }
private:
    fun  m_fun;
};

//class C: public A, public B
class C: public A, public boost::enable_shared_from_this<C>
{
public:
    virtual void print()
    {
        std::cout << "C::print" << std::endl;
    }

    void world1(int arg)
    {
        std::cout << "C::world1" << std::endl;
    }

    void hello()
    {
        //std::cout << "hello" << std::endl;
        D d(boost::bind(&C::world1, shared_from_this(), _1));
        d.world();
    }
};



int main()
{
    //boost::shared_ptr<A> ptr(new (std::nothrow) C);
    //ptr->print();
    //ptr->hello();

    std::cout << "===================" << std::endl;
    //object below must be shared_ptr, because you have used shared_from_this
    boost::shared_ptr<C> c(new (std::nothrow) C);
    c->hello();

    return 0;
}

