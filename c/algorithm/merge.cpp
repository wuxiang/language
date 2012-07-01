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

//merge sort from down to up
void merge_element(std::array<int, 100>& arr, std::size_t low, std::size_t middle, std::size_t high)
{
    std::vector<int>  temp;

    std::size_t index = 0;
    std::size_t i = low;
    std::size_t j = middle + 1;
    for (; i <= middle && j <= high; ++index)
    {
        if (arr[i] <= arr[j])
        {
            temp.push_back(arr[i]);
            ++i;
        }
        else
        {
            temp.push_back(arr[j]);
            ++j;
        }
    }

    while (i <= middle)
    {
        temp.push_back(arr[i]);
        ++i;
    }

    while (j <= middle)
    {
        temp.push_back(arr[j]);
        ++j;
    }

    for (std::size_t k = 0; k < temp.size(); ++k)
    {
        std::swap(temp[k], arr[low + k]);
    }
    //std::swap_ranges(arr.begin() + low, arr.begin() + high, temp.begin());
}

void merger_pass(std::array<int, 100>& arr, std::size_t length)
{
    std::size_t i = 0;
    for ( ; i + 2 * length <= arr.size(); i += 2 * length)
    {
        merge_element(arr, i, i + length -1, i + 2*length - 1);
    }

    if (i + length < arr.size())
    {
        merge_element(arr,i, i + length - 1, arr.size() - 1);
    }
	else
	{
		std::cout << "not change" << std::endl;
	}
}

void merger_sort(std::array<int, 100>& arr)
{
    for (std::size_t i = 1; i < arr.size(); i *= 2)
    {
        merger_pass(arr, i);
    }
}

//merge from up to down
void merge_element(int* arr, std::size_t low, std::size_t middle, std::size_t high)
{
    int*  temp = (int*)malloc((high - low + 1) * sizeof(int));

    std::size_t index = 0;
    std::size_t i = low;
    std::size_t j = middle + 1;
	int* start = temp;
    for (; i <= middle && j <= high; ++index)
    {
        if (arr[i] <= arr[j])
        {
            *(start + index) = arr[i++];
        }
        else
        {
            *(start + index) = arr[j++];
        }
    }

    while (i <= middle)
    {
        *(start + index++) = arr[i++];
    }

    while (j <= middle)
    {
        *(start + index++) = arr[j++];
    }

    for (std::size_t k = 0; k < index; ++k)
    {
        std::swap(*(temp + k), arr[low + k]);
    }
}

void up_merger_sort(int* arr, int low, int high)
{
	if (low < high)
	{
		int i = (low + high) / 2;
		up_merger_sort(arr, low, i);
		up_merger_sort(arr, i + 1, high);
		merge_element(arr, low, i, high);
	}
}

int main()
{
    std::array<int, 100> arr = number();
    //merger_sort(arr);
    print(arr);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
	up_merger_sort(&arr[0], 0, 99);
    print(arr);
    return 0;
}
