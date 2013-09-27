#include <iostream>

template<typename _T>
class  BNode
{
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
class BTree
{
public:
	BTree(): m_head(NULL)
	{
	}

	~BTree()
	{
		aftOrder(m_head, delNode);
	}

	void insert(_T&  val)
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

	void  delNode(BNode<_T>*  node)
	{
		delete node;
	}

private:
	BNode<_T>*  m_head;
};

template<typename _T>
class LinkNode
{
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
		return;
	}

	pCur->next = new LinkNode<_T>(node->data);
	pCur = pCur->next;
}

int main()
{
	return 0;
}
