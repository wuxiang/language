#include <iostream>

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdint.h>

#include <boost/thread.hpp>

int const  allocate_size = 100000;

uint64_t get_current_of_time()
{
    struct timeval  tm;
    gettimeofday(&tm, NULL);

    return (tm.tv_sec * 1000000 + tm.tv_usec);
}

void tc_allocate()
{
    uint64_t  strval = get_current_of_time();

    int * pInt = NULL;
    for (int i = 0; i < allocate_size; ++i)
    {
        pInt = new int;
        delete pInt;
    }

    printf("thread(%lu): %lu\n", pthread_self(), get_current_of_time() - strval);
}

int main()
{

    boost::thread exec1(tc_allocate);
    boost::thread exec2(tc_allocate);
    boost::thread exec3(tc_allocate);
    boost::thread exec4(tc_allocate);
    boost::thread exec5(tc_allocate);

    exec1.join();
    exec2.join();
    exec3.join();
    exec4.join();
    exec5.join();
    return 0;
}
