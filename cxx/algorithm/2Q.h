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

template<typename T, typename _TP>
class _2Q
{
private:
    uint64_t                    total;

    typedef typename std::unordered_map<T, std::pair<int, PITE> >::iterator idx_ite;
    typedef typename std::list<_TP>::iterator* PITE;
    typedef typename std::list<_TP>::iterator  ls_ite;

    boost::shared_mutex         index_mtx;
    boost::unordered_map<T, std::pair<int, PITE> > index;

    boost::shared_mutex         A1_mtx;
    std::list<_TP>              A1;

    boost::shared_mutex         Am_mtx;
    std::list<_TP>              Am;

public:
    _2Q(): total(0)
    {
    }

    ~_2Q()
    {
    }


    _TP* find(const T& key)
    {
    }

private:
    // index map handle
    bool index_get(const T& key, std::pair<int, PITE>& pir)
    {
        boost::shared_mutex<boost::shared_mutex> lock(index_mtx);
        idx it = index.find(key);
        if (it != index.end())
        {
            pir = *it;
            return true;
        }

        return false;
    }

    bool index_insert(const T& key, std::pair<int, PITE>& pir)
    {
        boost::unique_lock<boost::shared_mutex> lock(index_mtx);
        index.insert(std::make_pair(key, pir));
        return true;
    }

    bool index_del(const T& key)
    {
        boost::unique_lock<boost::shared_mutex> lock(index_mtx);
        index.erase(key);
        return true;
    }

    // A1 handle
    _TP once_get(ls_ite& it)
    {
        boost::unique_lock<boost::shared_mutex>  lock(A1_mtx);
        _TP  value =  *it;
        A1.erase(it);
        return value;
    }

    PITE once_insert(const _TP& val)
    {
        boost::unique_lock<boost::shared_mutex>  lock(A1_mtx);
        A1.push_front(val);
        return (&(A1.begin()));
    }

    virtual bool get_data(const T&  key)
    {
        return false;
    }

    bool update(const std::pair<int, PITE>& info)
    {
        return true;
    }
};

#endif //TWO_QUEUE_H_
