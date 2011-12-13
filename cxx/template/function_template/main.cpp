#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iterator>
#include "max.hpp"
#include "Stack.hpp"
#include "tracer.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
//#include "nested_template.hpp"

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
    std::vector<int>  s(10, 8);
    std::for_each(s.begin(), std::cout << '_1' << std::endl);
    std::vector<int>  d(10);
    std::transform(s.begin(), s.end(), d.begin(), addValue<int,8>);
    std::cout << d[0] << "," << d[9] << std::endl;
    //std::all_of(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, ""));

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

    try{
        Stack_non<int, 20>  int20Stack;
        int20Stack.push(7);
        std::cout << int20Stack.top() << std::endl;
        int20Stack.pop();
        int20Stack.pop();
    } catch(const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
	return 0;
}
