#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

/*****************
 * -v
 * -i int
 * -n char*
 * ***************/
bool getopt_func(int argc, char* argv[])
{
	bool flag = true;
	char*  optstring = "vi:n:";
	int res = 0;
	while (-1 != (res = getopt(argc, argv, optstring)))
	{
		switch (res)
		{
			case 'v':
				fprintf(stderr, "--version\n");
				break;
			case 'i':
				fprintf(stderr, "--i %d\n", *optarg);
				break;
			case 'n':
				fprintf(stderr, "--name %s\n", optarg);
				break;
			case '?':
				fprintf(stderr, "unknow case: %c\n", optopt);
				flag = false;
				break;
		}
	}
	return flag;
}

void getopt_long_func(int argc, char* argv[])
{
	bool flag = true;
	char*  optstring = "vi:n:";
	int optindex = 0;

	struct option options[] = {
								{"version", 0, NULL, 'v'},
								{"integer", 1, NULL, 'i'},
								{"name", 1, NULL, 'n'},
								{0, 0, 0, 0}};

	int res = 0;
	while (-1 != (res = getopt_long(argc, argv, optstring, options, &optindex)))
	{
		switch (res)
		{
			case 'v':
				fprintf(stderr, "--version\n");
				break;
			case 'i':
				fprintf(stderr, "--i %d\n", *optarg);
				break;
			case 'n':
				fprintf(stderr, "--name %s\n", optarg);
				break;
			case '?':
				fprintf(stderr, "unknow case: %c\n", optopt);
				flag = false;
				break;
		}
	}
	return flag;
}

int main(int argc, char* argv[])
{
	fprintf(stderr, "+++++++++++++++option parse begin++++++++++++++++++\n");
	//getopt_func(argc, argv);
	getopt_long_func(argc, argv);
	fprintf(stderr, "+++++++++++++++option parse end++++++++++++++++++\n");
	return 0;
}
