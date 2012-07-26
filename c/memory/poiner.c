#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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
    struct node* next;
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
	//printf("%d\n", *(&a[1] + 1));

    printf("++++++++++++++++++++address resolve++++++++++++++++++\n");
    struct node* left = (struct node*)malloc(sizeof(struct node));
    bzero((void*)left, sizeof(struct node));
    left->member = 8;
    printf("p::%p==>%p\n", &left, left);

    struct node* right = (struct node*)malloc(sizeof(struct node));
    bzero((void*)right, sizeof(struct node));
    right->member = 10;
    right->next = left;

    printf("right::%p==>%p\n", &right, right);

    printf("right::%p++>%p::v%d\n", &right + 0x1 , *(&right + 0x1),((struct node*)(*(&right + 0x1)))->member);
    printf("right->next::%p\n", &(right->next));
    printf("int::bytes::%lu\n", sizeof(int));

	return 0;
}

