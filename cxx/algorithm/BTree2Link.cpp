#include <iostream>
#include <sys/time.h>
#include <stdlib.h>

template<typename _T>
class  BNode
{
public:
	_T  data;
	BNode<_T>*  left;
	BNode<_T>*  right;

	BNode(): left(NULL), right(NULL)
	{
	}

	BNode(const _T& val): data(val)
	{
	}
};

template<typename _T>
class LinkNode
{
public:
	_T   sh;
	LinkNode<_T>* next;

	LinkNode(): next(NULL)
	{
	}

	LinkNode(const _T& val): sh(sh), next(NULL)
	{
	}
};


LinkNode<int>*  pHead;
LinkNode<int>*  pCur;

template<typename _T>
void exchange(BNode<_T>* node)
{
	if (!pHead)
	{
		pHead = pCur = new LinkNode<_T>(node->data);
		pHead->sh = node->data;
		pHead->next = NULL;
		return;
	}

	pCur->next = new LinkNode<_T>(node->data);
	pCur->next->sh = node->data;
	pCur->next->next = NULL;
	pCur = pCur->next;
}

void printLinkNode()
{
	pCur = pHead;
	while (pCur)
	{
		fprintf(stderr, "%d, ", pCur->sh);
		pCur = pCur->next;
	}
	fprintf(stderr, "\n");
}

template<typename _T>
class BTree
{
	private:
		//template<typename _T>
		static void  delNode(BNode<_T>*  node)
		{
			delete node;
		}

		//template<typename _T>
		static void printNode(BNode<_T>* node)
		{
			fprintf(stderr, "%d,", node->data);
		}

	public:
		BTree(): m_head(NULL)
	{
	}

		~BTree()
		{
			aftOrder(m_head, &delNode);
		}

		void insert(const _T&  val)
		{
			if (!m_head)
			{
				m_head = new BNode<_T>(val);;
				return;
			}

			BNode<_T>*  pre = NULL;
			BNode<_T>*  ptr = m_head;
			while(ptr)
			{
				pre = ptr;
				if (val < ptr->data)
				{
					ptr = ptr->left;
				}
				else if (val > ptr->data)
				{
					ptr =  ptr->right;
				}
				else
				{
					return;
				}
			}

			if (val < pre->data)
			{
				pre->left = new BNode<_T>(val);
			}
			else if (val > pre->data)
			{
				pre->right = new BNode<_T>(val);
			}
		}

		void midOrder(void (*func)(BNode<_T>*))
		{
			midOrder(m_head, func);
		}

		void preOrder(void (*func)(BNode<_T>*))
		{
			preOrder(m_head, func);
		}

		void aftOrder(void (*func)(BNode<_T>*))
		{
			aftOrder(m_head, func);
		}

		void print()
		{
			aftOrder(m_head, &printNode);
			printf("\n");
		}

		void charge()
		{
			aftOrder(m_head, &exchange);
		}

	private:
		void midOrder(BNode<_T>* node, void (*func)(BNode<_T>*))
		{
			if (!node)
			{
				return;
			}

			midOrder(node->left, func);
			func(node);
			midOrder(node->right, func);
		}

		void preOrder(BNode<_T>* node, void (*func)(BNode<_T>*))
		{
			if (!node)
			{
				return;
			}

			func(node);
			preOrder(node->left, func);
			preOrder(node->right, func);
		}

		void aftOrder(BNode<_T>* node, void (*func)(BNode<_T>*))
		{
			if (!node)
			{
				return;
			}

			aftOrder(node->left, func);
			aftOrder(node->right, func);
			func(node);
		}

	private:
		BNode<_T>*  m_head;
};

int main()
{
	pHead = pCur = NULL;
	srand(time(0));
	BTree<int>  tmp;
	for (int i = 0; i < 10; ++i)
	{
		tmp.insert(random() % 100);
	}
	tmp.print();

	tmp.charge();
	printLinkNode();
	return 0;
}
