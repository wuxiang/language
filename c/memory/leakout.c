#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

int main()
{
    printf("%d\n", getpid());
    void* p = malloc(1024);
    while(1)
    {
    }
    return 0;
}
