#include <iostream>
#include <string.h>

int main()
{
    char* a = "hello";
    char* b = "hello\0";
    std::cout << "len(a): " << strlen(a) << std::endl;
    std::cout << "len(b): " << strlen(b) << std::endl;
    std::cout << std::boolalpha << strcmp(a, b) << std::endl;
    std::cout << std::boolalpha << memcmp(a, b, strlen(a)) << std::endl;
    return 0;
}
