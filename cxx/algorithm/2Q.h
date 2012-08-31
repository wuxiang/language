/*********************************************
* *
* * the size of cache(250kb)
* * each tuple about 28 bytes
* *
* * *********************************************/
#ifndef TWO_QUEUE_H_
#define TWO_QUEUE_H_
#include <list>
#include <boost/unordered_map.hpp>

#include <boost/thread.hpp>
const std::size_t ONCE = 360;
const std::size_t OLDER = 840;

template<typename T, typename _TP>
class _2Q
{
public:
    _2Q()
    {
    }

    ~_2Q()
    {
    }



private:
    typedef typename std::list<_TP>::iterator* PITE;
    boost::shared_mutex         index_mtx;
    boost::unordered_map<T, std::pair<int, PITE> > index;

    boost::shared_mutex         A1_mtx;
    std::list<_TP>              A1;

    boost::shared_mutex         Am_mtx;
    std::list<_TP>              Am;
};

#endif //TWO_QUEUE_H_
