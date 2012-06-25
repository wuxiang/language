#include <iostream>
#include <vector>

struct numerical
{
    int value;
    numerical()
    {
        std::cout << "numerical::numerical" << __sync_add_and_fetch(&construct, 1) << std::endl;
    }

    //numerical(const int a): value(a)
    //{
    //    std::cout << "numerical::numerical" << __sync_add_and_fetch(&construct, 1) << std::endl;
    //}

    numerical(const int&& a): value(a)
    {
        std::cout << "numerical::numerical" << __sync_add_and_fetch(&construct, 1) << std::endl;
    }

    ~numerical()
    {
        std::cout << "~numerical::numerical" << __sync_add_and_fetch(&deconstruct, 1) << std::endl;
    }
    static int  construct;
    static int  deconstruct;
};
int numerical::construct = 0;
int numerical::deconstruct = 0;

void print(const numerical&& v)
{
    std::cout << "vector" << std::endl;
    std::vector<numerical>  vnum;

    std::cout << "first" << std::endl;
    vnum.push_back(v);

    std::cout << "second" << std::endl;
    vnum.push_back(10);
    std::cout << "end" << std::endl;
}

void print2(int&& test)
{
}

void print1(int& test)
{
    print2(test);
}

template<typename T>
T&& move(T&& a)
{
    return a;
}

template<typename T> 
void swap(T& a, T& b)
{
    T tmp(move(a));
    a = move(b);
    b = move(tmp);
}

int main()
{
    int a1 = 10;
    int& b1 = a1;
    //int&& b = 8;
    //int&& b = a;
    print(8);
    print1(a1);

    std::cout << "rvalue begin()" << std::endl;
    int a = 1;
    int b = 2;
    swap(a, b);
    std::cout << "rvalue end()" << std::endl;

    //std::vector<numerical>  vnum;
    //std::cout << "begin" << std::endl;
    //vnum.push_back(10);
    //std::cout << "success" << std::endl;
    return 0;
}
