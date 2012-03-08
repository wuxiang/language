#include <iostream>
#include <stdio.h>
#include <stdint.h>

int main()
{
    char c[256];
    for(int i=0; i < 256; ++i)
    {
        std::cout << std::hex << i << '\n';
        c[i] = i & 0xff;
    }
    fflush(NULL);

    uint8_t it = 0;
    for(int i=0; i < 256; ++i)
    {
        it = it | (c[i] & 0xff);
        //std::cout << it << ",";
        printf("%x,", it);
        it = 0;
        //printf("%c, ", c[i]);
    }

    printf("\n");
    return 0;
}
