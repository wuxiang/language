#include <stdio.h>
//#define __MICRO
#if defined(__MICRO)
    #define __GREET__ {printf("%s\n", "hello");}
#else
    #define __GREET__ {printf("%s\n", "world");}
#endif

int main()
{
    __GREET__
    return 0;
}
