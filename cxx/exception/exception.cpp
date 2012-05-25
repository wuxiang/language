#include <iostream>
#include <exception>
class myexception: public std::exception
{
    public:
        virtual const char* what() const throw()
        {
            return "happen in exception";
        }
};

void tr() throw(myexception)
{
    std::cout << "you will dead" << std::endl;
    throw  myexception();
}

int main()
{
    int index = 5;
    try {
        if (0 == index)
        {
            std::cout << "hello 0" << std::endl;
        }
        else if (1 == index)
        {
            std::cout << "hello 1" << std::endl;
        }
        else if (2 == index)
        {
            std::cout << "hello 2" << std::endl;
        }
        else if (3 == index)
        {
            std::cout << "hello 3" << std::endl;
        }
        else if (4 == index)
        {
            std::cout << "hello 4" << std::endl;
        }
        else if (5 == index)
        {
            std::cout << "hello 5" << std::endl;
            tr();
        }
        else if (6 == index)
        {
            std::cout << "hello 0" << std::endl;
        }
        else
        {
            throw std::exception();
        }
    } catch (const myexception& e){
        std::cout << "i have catch myexception" << std::endl;
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "an unknow exception happen" << std::endl;
    }

    return 0;
}
