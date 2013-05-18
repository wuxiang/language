#include <iostream>

class MyClass
{
	public:
		MyClass()
		{
			std::cout << "1" << std::endl;
		}
};

int main()
{
	std::cout << "a" << std::endl;
	MyClass a;
	std::cout << "b[2]" << std::endl;
	MyClass b[2];
	std::cout << "*p[2]" << std::endl;
	MyClass *p[2];
	std::cout << std::endl;
	return 0;
}
