#include <iostream>
#include <algorithm>
#include <array>

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

void fast_sort(std::array<int, 100>& arr, const int left, const int right)
{
	if (left >= right)
	{
		return;
	}

	int middle = arr[left];
	std::cout << "middle: " << middle << std::endl;

	int l = left + 1;
	int r = right;

	while (1)
	{
		//look up data from left to right
		while(arr[l] <= middle && l < r)
		{
			++l;
		} 

		//look up data from right to left
		while(arr[r] > middle && l <= r)
		{
			--r;
		} 

		if (l >= r)
		{
			std::cout << "break" << "\n";
			break;
		}

		std::swap(arr[l], arr[r]);
	}

	std::cout << arr[r] << std::endl;
	arr[left] = arr[r];
	arr[r] = middle;
	
	fast_sort(arr, left, r - 1);
	fast_sort(arr, r + 1, right);
}

int main()
{
	std::array<int, 100>  arr = number();
	fast_sort(arr, 0, 99);
	print(arr);
	return 0;
}
