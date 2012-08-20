#include <stdio.h>
#include <semaphore.h>
#include <time.h>

int main()
{
    struct timespec  tm;
    tm.tv_sec = 100000;
    tm.tv_nsec = 100000;

    sem_t  sem;

    sem_init(&sem, 0, 0);

    printf("waiting\n");

    if (0 == sem_timedwait(&sem, &tm))
    {
        printf("success\n");
    }
    else
    {
        printf("time out\n");
    }

    printf("end\n");

    sem_destroy(&sem);
    return 0;
}
