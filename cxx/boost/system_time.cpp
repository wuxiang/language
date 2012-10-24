#include <boost/thread.hpp>
#include <iostream>

int main()
{
    boost::condition_variable cond;
    boost::mutex mtx;

    //boost::lock_guard<boost::mutex> lock(mtx);
    boost::mutex::scoped_lock lock(mtx);
    std::cout << "+++++++++++++begin wait+++++++++++++" << std::endl;
    while(cond.timed_wait(lock, (boost::get_system_time() + boost::posix_time::milliseconds(3000))));
    std::cout << "+++++++++++++begin end+++++++++++++" << std::endl;
    return 0;
}
