#include <iostream>
#include <set>

#include <boost/thread/thread.hpp>
#include <boost/thread/tss.hpp>

boost::thread_specific_ptr<int>   ptr;

class manager
{
    public:
        static manager& instance()
        {
            static manager mgr;
            return mgr;
        }

        bool insert(int* ptr)
        {
            m_set.insert(ptr);
            return true;
        }

        int* get()
        {
            bool flag = true;
            std::set<int*>::iterator it;
            while (flag)
            {
                it = m_set.begin();
                if (it == m_set.end())
                {
                    continue;
                }
                else
                {
                    flag = false;
                }
            }

            return *it;
        }

        void print()
        {
            std::set<int*>::iterator it = m_set.begin();
            for (; it != m_set.end(); ++it)
            {
                std::cout << **it << std::endl;
            }
        }

    private:
        std::set<int*>  m_set;
};

class executor1
{
    public:
        void operator()()
        {
            ptr.reset(new (std::nothrow) int(0));
            std::cout << "thread 1: " << *ptr << std::endl;
            manager::instance().insert(ptr.get());
            std::cout << "thread 1: " << *ptr << std::endl;
            sleep(10);
            std::cout << "thread 1: " << *ptr << std::endl;
        }

        ~executor1()
        {
            //std::cout << "thread 1" << *ptr << std::endl;
        }
};

class executor2
{
public:
    void operator()()
    {
        int* p = manager::instance().get();
        *p = 100;

         ptr.reset(new (std::nothrow) int(200));
        std::cout << "thread 2: " << *ptr << std::endl;
    }

    ~executor2()
    {
        //std::cout << "thread 2" << *ptr << std::endl;
    }
};

int main()
{
    executor1 e;
    boost::thread t1(e);

    executor2 e2;
    boost::thread t2(e2);

    //manager::instance().print();
    t2.join();
    //manager::instance().print();
    sleep(10);
    return 0;
}
