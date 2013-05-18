#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//动态申请二维数组
template <typename T>
T** malloc_Array2D(int row, int col)
{
    int size = sizeof(T);
    int point_size = sizeof(T*);
    //先申请内存，其中point_size * row表示存放row个行指针
    T **arr = (T **) malloc(point_size * row + size * row * col);
    if (arr != NULL)
    {
        memset(arr, 0, point_size * row + size * row * col);
        T *head = (T*)((int)arr + point_size * row);
        while (row--)
            arr[row] = (T*)((int)head + row * col * size);
    }
    return (T**)arr;
}
//释放二维数组
void free_Aarray2D(void **arr)
{
    if (arr != NULL)
        free(arr);
}

int main()
{
    //fang an 1
    //const int col = 3;
    //int row = 0;
    //std::cin >> row;
    //
    //int* p = new int[fix * row];
    //int (*pArr)[fix] = (int(*)[fix])p;

    // fang an 2
     printf("请输入行列(以空格分开): ");
    int row, col;
    scanf("%d %d", &row, &col);

    //动态申请连续的二维数组
    int **pArr = malloc_Array2D<int>(row, col);

    int idx = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
	    pArr[i][j] = idx++;
        }
    }

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
	    std::cout << pArr[i][j] << std::endl;
        }
    }
    return 0;
}
