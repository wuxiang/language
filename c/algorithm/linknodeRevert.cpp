#include <stdio.h>

struct node
{
	int value;
	struct node* next;
};

void revert(struct node*& head)
{
	if (!head || !head->next)
	{
		return;
	}

	struct node* pHead = NULL;
	struct node* pCurr = NULL;
	struct node* pNext = head;

	do {
		pCurr = pNext;
		pNext = pNext->next;
		pCurr->next = pHead;
		pHead = pCurr;
	} while (pNext);

	head = pHead;
}

int main()
{
	struct node* head = new node();
	head->value = 88;
	head->next = NULL;
	struct node* pos = head;
	for (int i = 0; i < 10; ++i)
	{
		struct node* pV = new node;
		pV->value = i;
		pV->next = NULL;
		pos->next = pV;
		pos = pV;
	}

	revert(head);

	while (head)
	{
		printf("%d, %p\t", head->value, head->next);
		head = head->next;
	}
	printf("\n");
}
