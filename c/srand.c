#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANGE 13

int main()
{
    srand(time(NULL));
    int random = rand();

    printf("srand number: %d\n", random%RANGE);
    return 0;
}
