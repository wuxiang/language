#include <stdio.h>

#include <iostream>
#include <list>

int main()
{
    char* arr[4] = {"hello", "world", "tim", "wu"};

    std::list<char*>  lst(arr, arr + 4);

    for (std::list<char*>::iterator it = lst.begin(); it != lst.end(); ++it)
    {
        printf("%s\n", *it);
    }

    return 0;
}
