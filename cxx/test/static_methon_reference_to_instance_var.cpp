#include <iostream>
#include <string>

class obj
{
private:
	std::string m_test;
	static std::string m_mem;

public:
	obj(): m_test("hello")
	{
	}

	void print()
	{
		std::cout << m_mem << std::endl;
	}

	static void print_mem()
	{
		obj  o;
		o.print();
		std::cout << /*m_test << */m_mem << std::endl;
	}
};

std::string obj::m_mem = "world";

int main()
{
	obj o;

	return 0;
}
