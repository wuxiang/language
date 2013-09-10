#include <stdio.h>

struct TreeNode
{
	int value;
	TreeNode* leftChild;
	TreeNode* rightChild;
	TreeNode* parent;
};

void PrintTreeLevel(const TreeNode* root, int depth)
{
	if (!root)
	{
		return;
	}

	if (0 == depth)
	{
		fprintf(stderr, "%d\n", root->value);
	}
	else
	{
		PrintTreeLevel(root->leftChild, depth - 1);
		PrintTreeLevel(root->rightChild, depth - 1);
	}
}

int main()
{
	TreeNode  root[7];
	for (int i = 0; i < 7; ++i)
	{
		root[i].value = 0;
		root[i].leftChild = NULL;
		root[i].rightChild = NULL;
		root[i].parent = NULL;
	}

	root[0].value = 8;
	root[1].value = 6;
	root[2].value = 10;
	root[3].value = 5;
	root[4].value = 7;
	root[5].value = 9;
	root[6].value = 11;

	for (int i = 0; i < 3; ++i)
	{
		root[i].leftChild = root + (2 * i + 1);
		root[i].rightChild = root + (2 * i + 2);
	}

	for (int i = 1; i < 7; ++i)
	{
		root[i].parent = root + ((i - 1) / 2);
	}

	int  level = 2;
	PrintTreeLevel(root,  level);
	return 0;
}
