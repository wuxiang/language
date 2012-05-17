#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define  SIZE        6
int serial = 0;
pthread_t     threads[SIZE];

void sig_handle(int arg)
{
    int i = 0;
    for (i = 0; i < SIZE; ++i)
    {
        pthread_cancel(threads[i]);
    }
}

void* thread_start1(void* arg)
{
    while(1)
    {
        int start_value = 0;
        __sync_synchronize();
        start_value = serial;
        __sync_synchronize();
        printf("\n");
        printf("thread[%lu] get start value:%d\n", pthread_self(), start_value);
        printf("\n");

        int result = 0;
        result  = __sync_add_and_fetch(&serial, 1);
        printf("\n");
        printf("thread[%lu] fetch value after add: %d\n", pthread_self(), result);
        printf("\n");
    }
    return NULL;
}

int main()
{
    //signal(SIGINT, sig_handle);
    //signal(SIGQUIT, sig_handle);
    int i = 0;
    for (i = 0; i < SIZE; ++i)
    {
        pthread_create(&threads[i], NULL, thread_start1, NULL);
    }

    for (i = 0; i < SIZE; ++i)
    {
        printf("==>%lu\n", threads[i]);
    }

    sigset_t   wait_set;
    sigemptyset(&wait_set);
    sigaddset(&wait_set, SIGINT);
    sigaddset(&wait_set, SIGQUIT);
    pthread_sigmask(SIG_BLOCK, &wait_set, NULL);

    int sig = 0;
    sigwait(&wait_set, &sig);

    return 0;
}
