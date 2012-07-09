#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int arr1[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int* p = arr;

    printf("%d\n", arr[++p - arr]);
    printf("%d==>%d\n", *(*arr1 + 5), arr1[1][1]);
    return 0;
}
