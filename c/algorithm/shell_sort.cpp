/**************************************
 * shell sort similar to insert sort,
 * it divid totoal data to servel columns across by step
 * and sorted by columns,
*************************************/

#include <iostream>
#include <algorithm>
#include <array>

#include <stdio.h>
#include <stdlib.h>

//produce number for sort
std::array<int, 100>&&  number()
{
	std::array<int, 100>  arr;
	srand(time(NULL));
	for (int i = 0; i < 100; ++i)
	{
		arr[i] = rand() % 100;
	}

	return std::move(arr);
}

//print result which number has been sorted
void print(const std::array<int, 100>& arr)
{
	int flag = -1;   //each line shall be 10 number
	for (int i = 0; i < 100; ++i)
	{
		++flag;
		if ( flag  == 5)
		{
			flag = 0;
			std::cout << "\n";
		}

		std::cout << arr[i] << '\t';
	}
	std::cout << "\n";
}

void shell_sort(int* arr, int length)
{
    for (int step = length / 2; step > 0; step /= 2)
    {
        for(int i = step; i < length; ++i)
        {
            for (int j = i - step; j >= 0; j -= step)
            {
                if (*(arr + j + step) < *(arr + j))
                {
                    std::swap(*(arr + j), *(arr + j + step));
                }
            }
        }
    }
}

int main()
{
    std::array<int, 100> arr = number();
    shell_sort(&arr[0], 100);
    print(arr);
    return 0;
}
