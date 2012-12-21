#include "newlib.h"

Hello::Hello(const std::string& name): m_name(name), m_separate("\t")
{
}

void Hello::greet()
{
    std::cout << "hello " << m_separate << m_name << std::endl;
}

