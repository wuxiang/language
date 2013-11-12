#include <iostream>
#include <string>
#include <wchar.h>

int main()
{
	std::string value;
	value = "你好，你还好吗？";
	std::cout << value << sizeof(wchar_t) << std::endl;
	std::string h(31);
	std::cout << h << std::endl;
}
