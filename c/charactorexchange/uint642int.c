#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

int main()
{
	struct  timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t num = tv.tv_sec * 1000000 + tv.tv_usec;
	fprintf(stderr, "%llu\n", num);

	int64_t inum = num;
	fprintf(stderr, "%lld\n", inum);
	uint64_t  res = inum;
	fprintf(stderr, "%llu\n", res);
	return 0;
}
