#include <iostream>
#include <tuple>
#include <string>

template<class Tuple, std::size_t N>
struct TuplePrinter
{
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::print(t);
        std::cout << "," << std::get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
    std::cout << "sizeof = " << (sizeof...(Args)) << std::endl;
}

int main()
{
    std::tuple<int, std::string, float> t1(10, "test", 3.14);

    int n = 7;

    //auto t2 = std::tuple_cat(t1, std::make_pair("Foo", "bar"), t1, std::tie(n));

    n = 10;

    print(t1);
    //print(t2);

    return 0;
}
