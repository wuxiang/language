#include <stdio.h>
#include <stdint.h>

int main()
{
    uint64_t  num = 0xfefcfbfa;
    printf("%x, %x\n", *(unsigned char*)(&num), *((unsigned char*)(&num) + 3));
    return 0;
}
