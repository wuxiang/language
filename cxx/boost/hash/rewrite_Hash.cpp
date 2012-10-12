/******************************************************
  **
  ** write a example which use user define object and class that has exist in other library
  ** as the key in unordered_map and unordered_set
  **
 ******************************************************/

#include <iostream>
#include <boost/thread.hpp>
#include <pthread.h>
#include <stdio.h>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/thread.hpp>
#include <boost/functional/hash.hpp>
struct my
{
	int a;
	friend bool operator == (const my& y, const my& m)
	{
		return (y.a == m.a);
	}

	friend std::size_t  hash_value(const my& id);
};

// hash_value is called in boost::Hash, so my's Hash is implemented default;
std::size_t  hash_value(const my& id)
{
	std::size_t  seed = 0;
	boost::hash_combine(seed, boost::hash_value(id.a));
	return seed;
}

//std::size_t  hash_value(const  boost::thread::id& id)
//{
//	return 100;
//}

struct thread_id
{
	std::size_t operator()(const boost::thread::id& id)
	{
		std::ostringstream oss;
		oss << id;
		boost::hash<std::string> hs;
		return hs(oss.str());
	}
};
/********************************************
 * *
 * *namespace boost {
 * *  template<
 * *     class Key,
 * *     class Hash = boost::hash<Key>,
 * *     class Pred = std::equal_to<Key>,
 * *     class Alloc = std::allocator<Key> >
 * *  class unordered_set;
 *
 * *  template<
 * *     class Key,
 * *     class Hash = boost::hash<Key>,
 * *     class Pred = std::equal_to<Key>,
 * *     class Alloc = std::allocator<Key> >
 * *  class unordered_map;
 * *
 * *  template<typename T>
 * *  struct hash: public std::unary_function<T, std::size_t>{
 * *    std::size_t operator()(T const&) const;
 * * };
 * *
 * * advantage:  use template for implementing the extension of unordered_set's and unordered_map's Hash
 ********************************************/

namespace boost
{
template<>
struct hash<boost::thread::id>: public std::unary_function<boost::thread::id, std::size_t>
{
	std::size_t operator()(const boost::thread::id& id) const
	{
		return 100;
	}
};
}

int main()
{
	std::ostringstream  oss;
	boost::thread::id  th = boost::this_thread::get_id();
	oss << th;
	std::string idAsString = oss.str();
	std::cout << idAsString << std::endl;
	std::cout << boost::this_thread::get_id() << std::endl;
	unsigned int t = pthread_self();
	printf("%x\n", t);


	//boost::unordered_set<boost::thread::id>  setl;
	//setl.insert(th);

	boost::unordered_set<my> setm;
	setm.insert(my());

	std::cout << th << std::endl;
	boost::unordered_set<boost::thread::id>  id_set;
	id_set.insert(th);
	std::cout << *(id_set.begin()) << std::endl;

	return 0;
}
