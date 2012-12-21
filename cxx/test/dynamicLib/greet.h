#ifndef _LIB_H_
#define _LIB_H_

#include <iostream>
#include <string>

class Hello
{
public:
    Hello(const std::string& name);
    void greet();

private:
    std::string  m_name;
};

void say_sorry();

#endif
