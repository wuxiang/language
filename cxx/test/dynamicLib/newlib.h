#ifndef _NEWLIB_H_
#define _NEWLIB_H_

#include <iostream>
#include <string>

class Hello
{
public:
    Hello(const std::string& name);

    void greet();

private:
    std::string  m_separate;
    std::string  m_name;
};
#endif
