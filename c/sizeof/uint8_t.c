#include <stdio.h>
#include <stdint.h>

int main()
{
    printf("uint8_t size=>%lu\n", sizeof(uint8_t));
    printf("uint32_t size=>%lu\n", sizeof(uint32_t));
    printf("uint64_t size=>%lu\n", sizeof(uint64_t));

    uint8_t        a;
    uint32_t       b;
    uint64_t       c;
    printf("a==>%ld\n", sizeof(a));
    printf("b==>%ld\n", sizeof(b));
    printf("c==>%ld\n", sizeof(c));
    return 0;
}
