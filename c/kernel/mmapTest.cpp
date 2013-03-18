/*
 * mmap: a file can be mmap server times in single process or threads
 *       but is limited by mmaped file size, if size small, it can be more times
 *       or less times
 * /
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>

char* filename = "helloworld";

void* routine(void* arg)
{
	for (int i = 0; i < 10; ++i)
	{
		int fd  = 0;
		if (-1 == (fd = open(filename, O_RDWR|O_CREAT, S_IRWXU)))
		{
			printf("open failed\n");
		}

		void * ptr = mmap(NULL, 102400000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		if (ptr == MAP_FAILED)
		{
			printf("mmap failed1\n");
			exit(0);
		}
	}
	printf("thread exiting\n");
	pthread_exit(NULL);
}

int main()
{
	pthread_t   id;
	pthread_create(&id, NULL, routine, NULL);

	for (int i = 0; i < 10; ++i)
	{
		int fd  = 0;
		if (-1 == (fd = open(filename, O_RDWR|O_CREAT, S_IRWXU)))
		{
			fprintf(stderr, "open failed\n");
		}

		void * ptr = mmap(NULL, 1024000000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		if (ptr == MAP_FAILED)
		{
			fprintf(stderr, "mmap failed1\n");
			exit(0);
		}
		close(fd);
	}

	//sleep(10);

	//void * ptr1 = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	//if (ptr1 == MAP_FAILED)
	//{
	//	printf("mmap failed2\n");
	//}
	printf("program waiting\n");
	pthread_join(id, NULL);
	printf("program exiting\n");
	return 0;
}
