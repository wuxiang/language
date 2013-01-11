#include <stdio.h>

int main()
{
	printf("+++++++++++++++++begin+++++++++++++++++++");
	char*  p = "\x0a";
	printf("%s", p);
	printf("++++++++++++++++++end+++++++++++++++++++\x0a");
	return  0;
}
