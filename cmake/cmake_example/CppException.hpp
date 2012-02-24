// CppException.hpp

#ifndef _CppException_HPP_
#define _CppException_HPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// This file defines an exception handling class to be used with
// the rest of the code. 
class CppException
{
  public:
    CppException( const char* m );
    void Report() const;
    const char* message;
};

#endif
