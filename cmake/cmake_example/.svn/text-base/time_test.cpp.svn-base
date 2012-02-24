#include <iostream>
#include "Time.hpp"
#include "CppException.hpp"

//---------------------------------------------------------------------------//
// test the bounds on the Time class
void test_time_1()
{
  std::cout << "*** time test 1 ***" << std::endl;

  // try to set negative start time
  Time time_neg(-50, 10);

}

//---------------------------------------------------------------------------//
void test_time_2()
{
  std::cout << "*** time test 2 ***" << std::endl;

  // try to set end before begin time
  Time time_order(50, 10);

}

//---------------------------------------------------------------------------//
// the main program
int main()
{
  try
  {
    test_time_1();
    // Traditional unix programs return a non-zero value to indicate there was
    // an error in the program.  If we reach this point in the program, it means
    // our exception was not thrown as expected and the test failed.
    return 1;
  }
  // catch error of type CppException
  catch (const CppException & err)
  {
    err.Report();
  }

  try
  {
    test_time_2();
    return 1;
  }
  // catch error of type CppException
  catch (const CppException & err)
  {
    err.Report();
  }

  return 0;
}
