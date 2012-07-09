#include <stdio.h>
#define _HELLO

#if defined(_HELLO)
#define out(s) \
    printf("hello %s\n", s);
#else 
#define out(s) \
    printf("world %s\n", s);
#endif

int main()
{
    char* a = "jim";
    out(a);
    return 0;
}
