#include <stdio.h>
#include <stdlib.h>

int main()
{
	void* p = malloc(1024);
	int i = 0;
	void* ptr = NULL;
	while (1)
	{
		++i;
		ptr = realloc(p, i * 2048);

		if (ptr != p)
		{
			fprintf(stderr, "ptr != p\n");
			fprintf(stderr, "%p, %p\n", ptr ,p);
			break;
		}

		if (i >= 100)
		{
			fprintf(stderr, "i:%d >= 20\n", i);
			break;
		}

		p = ptr;
	}
	return 0;
}
