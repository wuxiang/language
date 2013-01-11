#include <iostream>

int main()
{
	int s_value = -109;
	int u_value = 109;

	//for signed int
	int div = s_value / 10;
	int lf = s_value % 10;
	int num = div * 10 + lf;
	std::cout << div << "==>" << lf << std::endl;
	std::cout << num << std::endl;

	//for unsigned int

	return 0;
}
