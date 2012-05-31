#include <iostream>
#include <vector>
#include <string>
#include <boost/any.hpp>

int main()
{
    std::vector<boost::any>  vec;

    //push int
    boost::any value1 = 8;
    vec.push_back(value1);

    //push char*
    const char* pc = "hello";
    vec.push_back(pc);

    //push std::string
    std::string str = "hello";
    value1 = str;
    vec.push_back(value1);

    for(std::size_t i =0; i < vec.size(); ++i)
    {

        //boost::any&   any = vec[i];
        //std::cout << vec[i].type() << std::endl; boost::any not support ostream
        if (vec[i].type() == typeid(int))
        {
        std::cout << "int" << std::endl;
        }
    }
    return 0;
}
