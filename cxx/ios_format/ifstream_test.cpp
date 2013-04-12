#include <iostream>
#include <fstream>
#include <string>

int main()
{
	char* file = "char.cpp";
	std::ifstream  in(file);
	std::string value;
	while (in.good())
	{
		value.clear();
		in >> value;
		std::cout << value;
	}
	return 0;
}
