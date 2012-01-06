#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_key_t  key;
//char* pData;

void* thread_routin1(void* arg)
{
    printf("starting thread_routin\n");
    // private data
    char* pData = (char*)malloc(sizeof(char)*strlen("hello world"));
    if (0 != pthread_setspecific(key, pData))
    {
        fprintf(stderr, "error happened when set special data in %s\n", (char*)arg);
    }

    // change data
    strcpy(pData, "the private");
    sleep(3);

    pData = (char*)pthread_getspecific(key);
    printf("$%s\n", pData);
    printf("ending thread_routin\n");
    return NULL;
}

void* thread_routin2(void* arg)
{
    printf("starting thread_routin\n");
    // private data
    char* pData = (char*)malloc(sizeof(char)*strlen("hello world"));
    if (0 != pthread_setspecific(key, pData))
    {
        fprintf(stderr, "error happened when set special data in %s\n", (char*)arg);
    }

    // change data
    strcpy(pData, "the second");

    pData = (char*)pthread_getspecific(key);
    printf("$%s\n", pData);
    printf("ending thread_routin\n");
    return NULL;
}

int main()
{
    //pData = (char*)malloc(sizeof(char)*strlen("hello world"));
    // create private key
    if (0 != pthread_key_create(&key, NULL))
    {
        fprintf(stderr, "error happened when create thread key\n");
        exit(EXIT_FAILURE);
    }

    pthread_t thread1;
    pthread_t thread2;
    int status;

    status = pthread_create(&thread1, NULL, thread_routin1, "thread 1");
    if (status != 0)
    {
        printf("error when create pthread1\n");
    }

    status = pthread_create(&thread2, NULL, thread_routin2, ("thread 2"));
    if (status != 0)
    {
        printf("error when create pthread1\n");
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}

