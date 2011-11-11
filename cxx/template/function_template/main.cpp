#include <iostream>
#include "max.hpp"

int main()
{
	//1, deduction arguement	
	std::cout << s_max(10, 20) << std::endl;
	//2, specified arguement
	std::cout << s_max<double>(10, 1.1) << std::endl;
    std::cout << s_max(10, 1.1) << std::endl;
	return 0;
}
