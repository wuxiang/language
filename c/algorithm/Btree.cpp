#include <iostream>


template<typename T>
struct BTreeNode
{
	BTreeNode(const T& dt)
	{
		data = dt;
		left = NULL;
		right = NULL;
	}

	T data;
	BTreeNode<T>*  left;
	BTreeNode<T>*  right;
};

template<typename T>
class BTree
{
public:
	BTree();
	~BTree();

	//insert
	bool insert(BTreeNode<T>* node);
	bool insert(const T&  element);

	//search
	bool preOrder(void (*visit) (BTreeNode<T>*));
	bool inOrder(void (*visit) (BTreeNode<T>*));
	bool postOrder(void (*visit) (BTreeNode<T>*));

	//attribute
	bool is_empty() const;
	int  depth() const;
	int  node() const;
	void print();

protected:
	bool preOrder(void (*visit) (BTreeNode<T>*), BTreeNode<T>* t);
	bool inOrder(void (*visit) (BTreeNode<T>*), BTreeNode<T>* t);
	bool postOrder(void (*visit) (BTreeNode<T>*), BTreeNode<T>* t);
	int  depth(const BTreeNode<T>* t) const;
	//void destroy(BTreeNode<T>* t);

private:
	BTreeNode<T>*  head;
	int            count;
};


//global function
template<typename T>
void destroy(BTreeNode<T>* t)
{
	delete t;
}

template<typename T>
void putout(BTreeNode<T>* t)
{
	std::cout << t->data << std::endl;
}

//member function
template<typename T>
BTree<T>::BTree(): head(NULL), count(0)
{
}

template<typename T>
BTree<T>::~BTree()
{
	postOrder(&destroy);
}

//template<typename T>
//void BTree<T>::destroy(BTreeNode<T>* t)
//{
//	delete t;
//}

template<typename T>
bool BTree<T>::insert(BTreeNode<T>* node)
{
	if (!head)
	{
		head = node;
		return true;
	}

	BTreeNode<T>* pTree = head;
	while (true)
	{
		if (node->data < pTree->data)
		{
			if (pTree->left == NULL)
			{
				pTree->left = node;
				break;
			}

			pTree = pTree->left;
		}
		else if (node->data > pTree->data)
		{
			if (pTree->right == NULL)
			{
				pTree->right = node;
				break;
			}

			pTree = pTree->right;
		}
		else
		{
			return false;
		}
	}

	return true;
}

template<typename T>
bool BTree<T>::insert(const T&  element)
{
	BTreeNode<T>* p = new BTreeNode<T>(element);
	insert(p);
}

template<typename T>
void BTree<T>::print()
{
	//postOrder(&putout, head);
	//preOrder(&putout, head);
	inOrder(&putout, head);
}

template<typename T>
bool BTree<T>::preOrder(void (*visit) (BTreeNode<T>*))
{
	preOrder(visit, head);
}

template<typename T>
bool BTree<T>::inOrder(void (*visit) (BTreeNode<T>*))
{
	inOrder(visit, head);
}

template<typename T>
bool BTree<T>::postOrder(void (*visit) (BTreeNode<T>*))
{
	postOrder(visit, head);
}


template<typename T>
bool BTree<T>::preOrder(void (*visit) (BTreeNode<T>*), BTreeNode<T>* t)
{
	if (t)
	{
		visit(t);
		preOrder(visit, t->left);
		preOrder(visit, t->right);
	}

	return true;
}

template<typename T>
bool BTree<T>::inOrder(void (*visit) (BTreeNode<T>*), BTreeNode<T>* t)
{
	if (t)
	{
		inOrder(visit, t->left);
		visit(t);
		inOrder(visit, t->right);
	}

	return true;
}

template<typename T>
bool BTree<T>::postOrder(void (*visit) (BTreeNode<T>*), BTreeNode<T>* t)
{
	if (t)
	{
		postOrder(visit, t->left);
		postOrder(visit, t->right);
		visit(t);
	}

	return true;
}

template<typename T>
bool BTree<T>::is_empty() const
{
	return !head ? true : false;
}

template<typename T>
int  BTree<T>::depth() const
{
	return depth(head);
}

template<typename T>
int  BTree<T>::depth(const BTreeNode<T>* t) const
{
	if (!t)
	{
		return 0;
	}

	int lf = depth(t->left);
	int rg = depth(t->right);
	return (lf > rg) ? ++lf : ++rg;
}

template<typename T>
int  BTree<T>::node() const
{
	return count;
}


int main()
{
	BTree<int>  btree;
	for (int i = 0; i < 10; ++i)
	{
		btree.insert(i);
	}

	btree.print();
}
