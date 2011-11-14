#include <iostream>
#include <string>
#include <cstdlib>
#include "max.hpp"
#include "Stack.hpp"

int main()
{
    //function template test
	//1, deduction arguement	
	//std::cout << s_max(10, 20) << std::endl;
	//2, specified arguement
	//std::cout << s_max<double>(10, 1.1) << std::endl;
    //std::cout << s_max(10, 1.1) << std::endl;
    //std::cout << s_max<>('a', 'b') << std::endl;
    //std::cout << s_max('a', 42.78) << std::endl;

    //class template test
    try {
        Stack<int>  intStack;
        Stack<std::string> stringStack;

        stringStack.push("hello");
        std::cout << stringStack.top() << std::endl;
        stringStack.pop();
        //stringStack.pop();
    } catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    try {
        Stack_t<int> intStack;
        intStack.push(7);
        std::cout << intStack.top() << std::endl;
        intStack.pop();

        Stack_t<double, std::deque<double> > dblStack;
        dblStack.push(42.42);
        std::cout << dblStack.top() << std::endl;
        dblStack.pop();
        dblStack.pop();
    } catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
	return 0;
}
