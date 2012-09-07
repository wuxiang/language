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
enum queue_num
{
    _ONCE_FLAG_,
    _SECOND_FLAG_,
};

const std::size_t TOTAL = 1200;
const std::size_t ONCE = 360;
const std::size_t OLDER = 840;

template<typename _T, typename _T_ITE>
struct _Info
{
    int         q_num;
    _T          value;
    _T_ITE      it;
};

template<typename T, typename _TP>
class _algrm_lru
{
private:
    uint64_t                    total;

    typedef typename std::list<T>::iterator  lt_ite;
    typedef typename boost::unordered_map<T, _Info<_TP,  lt_ite> >   LRU_map;

    boost::shared_mutex         index_mtx;
    LRU_map                     cnt;

    boost::shared_mutex         lst_mtx;
    std::list<T>                lst;

public:
    _algrm_lru(): total(0)
    {
    }

    ~_algrm_lru()
    {
    }


    //_TP* find(const T& key)
    //{
    //}

private:

    virtual bool get_data(const T&  key)
    {
        return false;
    }
};

#endif //TWO_QUEUE_H_
