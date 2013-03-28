#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int  arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int  arr1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int  arr2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int  arr3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	memcpy((void*)arr, (void*)&arr[4], sizeof(int) * 6);
	memcpy((void*)&arr1[4], (void*)&arr1, sizeof(int) * 6);

	memmove((void*)arr2, (void*)&arr2[4], sizeof(int) * 6);
	memmove((void*)&arr3[4], (void*)&arr3, sizeof(int) * 6);

	int i = 0;
	printf("memcpy arr(src > des)\n");
	for (; i < 10; ++i)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");

	int j = 0;
	printf("memcpy arr1(src < des)\n");
	for (; j < 10; ++j)
	{
		printf("%d\t", arr1[j]);
	}
	printf("\n");

	int m = 0;
	printf("memmove arr2(src > des)\n");
	for (; m < 10; ++m)
	{
		printf("%d\t", arr2[m]);
	}
	printf("\n");

	int n = 0;
	printf("memmove arr3(src < des)\n");
	for (; n < 10; ++n)
	{
		printf("%d\t", arr3[n]);
	}
	printf("\n");

	return 0;
}
