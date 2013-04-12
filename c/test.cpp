#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE* f = fopen("config.xml", "rb");
	if (!f)
	{
		printf("%s\n", strerror(errno));
	}
	return 0;
}
