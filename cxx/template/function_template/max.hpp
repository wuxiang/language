#include <iostream>
#include <string>

class userObj
{
};
const int s_max(const int a, const int b)
{
    return (a < b ? b : a);
}

//const int& s_max(const int& a, const int& b)
//{
//    return (a < b ? b : a);
//}

template<typename T>
const T&  s_max(const T& a, const T& b)
{
    std::cout << "template T" << std::endl;
	return (a > b ? a : b);
}

template<typename T1, typename T2>
const T2 s_max(const T1& a, const T2& b)
{
    std::cout << "template T2" << std::endl;
	return (a > b ? a : b);
}

template<typename T1, typename T2, typename T3>
const T1 s_max(const T2& a, const T3& b)
{
    std::cout << "template T1" << std::endl;
	return (a > b ? a : b);
}

template<typename T, int VAL>
T addValue(const T& x)
{
    return x + VAL;
}

template<>
int addValue<int, 8>(const int& x)
{
    return x + 9;
}

//template<typename T, userObj VAL>
//T AddValue(const T& x)
//{
//    return x + VAL;
//}
