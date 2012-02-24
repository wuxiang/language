#include "Organism.hpp"
#include <iostream>
#include <list>
#include <vector>
#include "Animal.hpp"
#include "CppException.hpp"

//---------------------------------------------------------------------------//
// test the animal class
void test_animal_1()
{
  std::cout << "animal test" << std::endl;

  std::vector<std::string> food;
  food.push_back("goats");

  // make an animal.
  Animal chupacabra("chupacabra", .7,2, food);

  // try to clone the animal
  Organism *chupacabra2 = chupacabra.clone();
  if (chupacabra2->getName() != chupacabra.getName())
    //throw &chupacabra;
    throw CppException("Failed to create animal using Organism clone function");

}

//---------------------------------------------------------------------------//
// the main program
int main()
{
  try
  {
    test_animal_1();
  }

  // catch error of type CppException
  catch (const CppException & err)
  {
    err.Report();
    return 1;
  }

  // catch numbered exception
  catch (const int item)
  {
    std::cout<< "Exception thrown, number: " << item <<  std::endl;
    return 1;
  }

  // catch any other exception
  catch (...)
  {
    std::cout<< "Unknown exception thrown." << std::endl;
    return 1;
  }

  return 0;
}
