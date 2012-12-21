//#ifndef _LIB_H_
//#define _LIB_H_
//
#include <iostream>
#include <string>
#include "greet.h"

Hello::Hello(const std::string& name): m_name(name)
{
}

void Hello::greet()
{
    std::cout << "hello " << m_name << std::endl;
}

void say_sorry()
{
    std::cout << "i am sorry" << std::endl;
}

//#endif
