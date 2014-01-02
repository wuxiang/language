#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void sigHandler(int sig)
{
	if (sig == SIGTERM)
	{
		fprintf(stderr, "get signal\n");
		exit(0);
	}
}

void* routine(void* parm)
{
	while(1);
	return (void*)NULL;
}

int main()
{
	//char* ptr = NULL;
	//*ptr = 'h';
	signal(SIGTERM, sigHandler);

	fprintf(stderr, "starting thread!!!\n");
	pthread_t idf;
	pthread_create(&idf, NULL, routine, NULL);

	pthread_t ids;
	pthread_create(&ids, NULL, routine, NULL);

	pthread_t idt;
	pthread_create(&idt, NULL, routine, NULL);

	pthread_t idj;
	pthread_create(&idj, NULL, routine, NULL);

	fprintf(stderr, "end create thread!!!\n");
	while(1);
	return 0;
}

