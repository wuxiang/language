#include <iostream>
#include <stdio.h>

int main()
{
	int* a = new int[0];
	//int* a = NULL;
	if (a == NULL)
	{
		std::cout << "NULL" << '\n';
		delete []a;
	}
	else
	{
		printf("%p\n", a);	
		std::cout << " NON NULL" << *(a + 100) << '\n';
		delete []a;
	}
	return 0;
}
