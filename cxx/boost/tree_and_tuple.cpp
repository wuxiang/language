#include <iostream>
#include <boost/unordered_set.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>

int main()
{
    boost::unordered_set<boost::tuple<int, std::string> > set;
    set.insert(boost::tuple<int, std::string>(1, std::string()));
    return 0;
}
