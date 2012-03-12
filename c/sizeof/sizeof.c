#include <stdio.h>
#include <stdlib.h>

void func(char c[100])
{
    printf("sizeof(c):%ld\n", sizeof(c));
}

int main()
{
    char b[100];
    func(b);
    printf("sizeof(b):%ld\n", sizeof(b));

    char* pchar = (char*)malloc(100);
    func(pchar);
    printf("sizeof(pchar):%ld\n", sizeof(pchar));
    return 0;
}
