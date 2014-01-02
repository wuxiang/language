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

struct node*  revertRecur(struct node*& first, struct node* head)
{
	if (!head || !head->next)
	{
		first = head;
		return head;
	}
	struct node* pTmp = head;

	struct node* pNode = revertRecur(first, head->next);
	pNode->next = pTmp;
	pTmp->next = NULL;

	return  pTmp;
}

int main()
{
	struct node* head = NULL;
	struct node* pos = NULL;
	for (int i = 0; i < 10; ++i)
	{
		struct node* pV = new node;
		pV->value = i;
		pV->next = NULL;

		if (!head)
		{
			head = pV;
			pos = head;
		}
		else
		{
			pos->next = pV;
			pos = pos->next;
		}
	}

	//revert(head);
	revertRecur(head, head);

	while (head)
	{
		//printf("%d\t"/*, %p\t*/, head->value/*, head->next*/);
		fprintf(stderr, "%d, %p\t\n", head->value, head/*->next*/);
		head = head->next;
	}
	printf("\n");
}
