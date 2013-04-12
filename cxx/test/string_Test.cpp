#include <iostream>
#include <string>

int main()
{
	std::string  uri = "http://www.baidu.com/index.html";
	std::string  head = "http://";
	std::string  heads = "https://";

	if (uri.compare(0, head.length(), head) == 0)
	{
		int pos = uri.find('/', head.length());
		std::cout << pos << std::endl;
		std::cout << head.length() << "::" << pos - head.length() << std::endl;
		std::string str = uri.substr(head.length(), pos - head.length());
		std::cout << str << std::endl;
	}
	else if (uri.compare(0, heads.length(), heads) == 0)
	{
	}

	return 0;
}
