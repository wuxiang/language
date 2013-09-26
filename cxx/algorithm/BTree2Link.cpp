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

	void midOrder(BNode<_T>* node, void (*func)(BNode<_T>*))
	{
	}

private:

private:
	BNode<_T>*  m_head;
};

int main()
{
	return 0;
}
