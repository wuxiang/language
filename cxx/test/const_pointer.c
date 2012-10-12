#include <stdio.h>

const char* const* pp;

int main()
{
    pp++;
    (*pp)++;
    (**pp) = 'c';
    return 0;
}
