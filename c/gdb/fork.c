#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    if (fork() == 0)
    {
        printf("hello child\n");
//        sleep(20);
        exit(0);
    }
    else
    {
        printf("hello parent\n");
//        sleep(20);
    }

    printf("termal\n");
    exit(0);
}
