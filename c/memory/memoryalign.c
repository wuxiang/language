/*********************************************
 * *
 * * c语言内存的对其规则：
 * * 对象前面的总内存数是该对象大小的整数倍，同时总的内存数是4的整数倍
 * *
 * ********************************************/
#include <stdio.h>

struct base
{
	char  a;
	char  b;
	int   c;
};

struct st
{
	int   c;
	char  a;
	char  b;
};

struct bs
{
	char  a;
	char  b;
	int   c;
	char  d;
	short e;
	char  f;
};


int main()
{
	printf("sizeof(base): %d\n", sizeof(struct base));
	printf("sizeof(st): %d\n", sizeof(struct st));
	printf("sizeof(bs): %d\n", sizeof(struct bs));
	return 0;
}
