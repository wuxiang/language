#include <stdio.h>
#include <stdint.h>

int main()
{
    uint64_t  num = 0xfefcfbfa;
    uint64_t tmp = num >> 8;
    printf("%x, %x\n", *(unsigned char*)(&num), *((unsigned char*)(&num) + 3));
    printf("%x\n", num);
    printf("%x\n", tmp);
    return 0;
}
