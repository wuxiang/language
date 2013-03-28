#include <stdio.h>

struct nstring
{
	int sz;
	char cnt[0];
};

int main()
{
	printf("nstring: %d\n", sizeof(struct nstring));
	return 0;
}
