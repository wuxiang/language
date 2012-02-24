#include <iostream>
#include "CppException.hpp"

// this file contains demonstrates throwing an integer exception,
// an unknown exception, and a CppException.

//---------------------------------------------------------------------------//
// test an integer exception
void test_int()
{
  std::cout << "*** integer exception test ***" << std::endl;
  throw 20;
}

//---------------------------------------------------------------------------//
// test an unknown exception
void test_unknown()
{
  std::cout << "*** unknown exception test ***" << std::endl;
  throw "what?";
}

//---------------------------------------------------------------------------//
// test a CppException
void test_CppException()
{
  std::cout << "*** CppException test ***" << std::endl;
  throw CppException("Threw a CppException!");
}

//---------------------------------------------------------------------------//
// the main program
int main()
{
  // run some tests
  try
  {
    test_int();
    // Traditional unix programs return a non-zero value to indicate there was
    // an error in the program.  If we reach this point in the program, it means
    // our exception was not thrown as expected and the test failed.
    return 1;
  }
  // catch numbered exception
  catch (const int item)
  {
    std::cout<< "Exception thrown, number: " << item <<  std::endl;
  }

  try 
  {
    test_unknown();
    return 1;
  }
  // catch any other exception
  catch (...)
  {
    std::cout<< "Unknown exception thrown." << std::endl;
  }

  try
  {
    test_CppException();
    return 1;
  }
  // catch error of type CppException
  catch (const CppException & err)
  {
    err.Report();
  }

  // Traditional unix programs return a value of '0' from main() to indicate
  // that the program exited normally.  In this case it means the test passed.
  return 0;
}
