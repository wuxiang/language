#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_routine(void* argv)
{
    while(1)
    {
        printf("waiting............\n");
        printf("collected\n");
    }
    return argv;
}

int main(int argc, char** argv)
{
    pthread_t id;
    if (pthread_create(&id, NULL, thread_routine, NULL))
    {
        printf("pthread_create error\n");
        return 1;
    }
    pthread_exit(EXIT_SUCCESS);
    printf("exiting\n");
    sleep(3);
    return 0;
}
