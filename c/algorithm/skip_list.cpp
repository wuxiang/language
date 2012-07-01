#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <deque>

template<typename _KT, typename _VT>   class skipList;

template<typename _KT, typename _VT>
class skip_node
{
	friend  class skipList<_KT, _VT>;
//	public:
	skip_node(int level)
	{
		if (level == 0)
		{
			link = NULL;
		}
		else
		{
			link = new skip_node<_KT, _VT>*[level];
		}
	}

	~skip_node()
	{
		delete []link;
	}

	_KT  key;
	_VT  value;
	skip_node<_KT, _VT>**   link;
};

template<typename _K, typename _V>
class skipList
{
	public:
		skipList(_K  large, float p);
		~skipList();
		bool search(const _K&   key, _V& value);
		skip_node<_K, _V>* insert(const _K&   key, const _V& value);
		skip_node<_K, _V>* del(const _K&   key);
		void   print();

	private:
		int level();
		skip_node<_K, _V>* search(const _K&  key, std::deque<skip_node<_K, _V>* >& node_level);

		skip_node<_K, _V>* head;
		skip_node<_K, _V>* tail;
		int cutoff;      //make sure level number
		_K   large;      //the largest key
		int  maxLevel;
		int  levels;    //number of level in the moment
};

template<typename _K, typename _V>
skipList<_K, _V>::skipList(_K  large, float p): large(large), levels(0)
{
	cutoff = p* RAND_MAX;
	maxLevel = ceil(log(large)/log(1/p)) - 1;

	head = new skip_node<_K, _V>(maxLevel);
	tail = new skip_node<_K, _V>(0);
	tail->key = large;

	for (int i = 0; i < maxLevel; ++i)
	{
		head->link[i] = tail;
	}
}

template<typename _K, typename _V>
skipList<_K, _V>::~skipList()
{
	skip_node<_K, _V>* pNode;
	while (head != tail)
	{
		pNode = head;
		head = head->link[0];
		delete pNode;
	}

	delete tail;
}

template<typename _K, typename _V>
bool skipList<_K, _V>::search(const _K&   key, _V& value)
{
	if (key > large)
	{
		return false;
	}

	skip_node<_K, _V>*  pNode = head;
	for (int i = levels; i >=0; ++i)
	{
		while (pNode->link[i].key < key && pNode->link[i] != tail)
		{
			pNode = pNode->link[i];
		}
	}

	value = pNode->link[0].value;

	return ((pNode->link[0].key == key) ? true : false);
}

template<typename _K, typename _V>
skip_node<_K, _V>* skipList<_K, _V>::insert(const _K&   key, const _V& value)
{
	if (key > large)
	{
		return NULL;
	}

	//get the information of node level
	std::deque<skip_node<_K, _V>* >  node_level;
	skip_node<_K, _V>* p = search(key, node_level);
	if (p->key == key && p->value == value)
	{
		return NULL;
	}

	int lev = level();

	//add a new level, but it is a probability event
	if (lev > levels)
	{
		lev = ++levels;
		node_level.push_back(head);
	}

	skip_node<_K, _V>*  new_node = new skip_node<_K, _V>(lev + 1);
	new_node->key = key;
	new_node->value = value;

	for (std::size_t i = 0; i <= lev; ++i)
	{
		new_node->link[i] = node_level[i]->link[i];
		node_level[i]->link[i] = new_node;
	}

	return new_node;
}

template<typename _K, typename _V>
skip_node<_K, _V>* skipList<_K, _V>::del(const _K&   key)
{
	if (key > large)
	{
		return NULL;
	}

	std::deque<skip_node<_K, _V>* >  node_level;
	skip_node<_K, _V>* p = search(key, node_level);
	if (p->key != key)
	{
		return NULL;
	}

	//remove  node(p)
	for (std::size_t i = 0; i < levels && node_level[i]->link[i] == p; ++i)
	{
		node_level[i]->link[i] = p->link[i];
	}

	// handle levels
	while (levels > 0 && head->link[levels] ==  tail)
	{
		--levels;
	}
}

template<typename _K, typename _V>
int skipList<_K, _V>::level()
{
	int lev = 0;
	while (rand() < cutoff)
	{
		++lev;
	}

	return (lev <= maxLevel ? lev : maxLevel);
}

template<typename _K, typename _V>
skip_node<_K, _V>* skipList<_K, _V>::search(const _K&  key, std::deque<skip_node<_K, _V>* >& node_level)
{
	skip_node<_K, _V>*  pNode = head;
	for (int i = levels; i >= 0; --i)
	{
		while (pNode->link[i]->key < key && pNode->link[i] != tail)
		{
			pNode = pNode->link[i];
		}
		node_level.push_front(pNode);
	}

	return pNode->link[0];
}

template<typename _K, typename _V>
void   skipList<_K, _V>::print()
{
	skip_node<_K, _V>*  pNode = NULL;
	for (int i = 0; i < levels; ++i)
	{
		printf("+++++++++++++++%d++++++++++++++++++\n", i);
		pNode = head->link[i];

		while (pNode != tail)
		{
			std::cout << "key:" << pNode->key << "=>" << pNode->value << "," << '\t';
			pNode = pNode->link[i];
		}
		std::cout << "\n";
	}
}

int main()
{
	skipList<int, std::string>         lst(2000, 0.5);
	std::string  value("hello");
	for (int i = 0; i < 100;  ++i)
	{
		lst.insert(i, value);
	}

	lst.print();

	return 0;
}
