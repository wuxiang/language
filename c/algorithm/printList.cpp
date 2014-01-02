#include <stdio.h>

struct  node
{
	int value;
	struct node* next;
};

int printLastFive(struct node* head)
{
	if (!head)
	{
		return -1;
	}

	struct node* start = head;
	struct node* post = head;
	size_t i = 1;
	while (post->next != NULL)
	{
		if (i < 5)
		{
			++i;
		}
		else
		{
			start = start->next;
		}

		post = post->next;
	}

	if (i < 5)
	{
		return -1;
	}

	return start->value;
};

int main()
{
	struct node* head = NULL;
	struct node* pos = NULL;
	for (int i = 0; i < 6; ++i)
	{
		if (i == 0)
		{
			head = pos = new node;
			head->value = i;
			head->next = NULL;
		}
		else
		{
			pos->next = new node;
			pos->next->value = i;
			pos->next->next = NULL;
			pos = pos->next;
		}
	}

	printf("%d\n", printLastFive(head));
	return  0;
}
