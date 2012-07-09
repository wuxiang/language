#include <stdio.h>

void print(int** a)
{
	for (int i = 0; i < 3; ++i)
	{
	  for (int j = 0; j < 4; ++j)
	  {
		  printf("%d\t", a[i][j]);
	  }
	  printf("\n");
	}
}

struct node
{
    int member;
    struct* node;
};

int main()
{
	int a[3][4];
	int index = 0;
	for (int i = 0; i < 3; ++i)
	{
	  for (int j = 0; j < 4; ++j)
	  {
		  a[i][j] = index++;
	  }
	}

	//print(a);

	printf("%d: %d\n", *(*(a+1) + 1), a[1][1]);
	printf("%d\n", *(&a[0][0] + 5));
	printf("%d\n", *(&a[1] + 1));

    printf("++++++++++++++++++++address resolve++++++++++++++++++\n");
    struct node* p = (struct node*)malloc(sizeof(struct node));
    bzero(p, sizeof(struct node));

    struct node* next = (struct node*)malloc(sizeof(struct node));
    bzero(next, sizeof(struct node));

	return 0;
}
