#include <stdio.h>
#include <stdlib.h>

int main()
{
	int*  p1, *p2;
	p1 = (int*)malloc(sizeof(int));
	p2 = (int*)malloc(sizeof(int));
	*p1 = 9;
	*p2 = 10;
	printf("*p1 = %d\n", *p1);
	return 0;
}
