#include "Organism.hpp"
#include <iostream>
#include <list>
#include "Time.hpp"
#include "Forest.hpp"
#include "Plant.hpp"
#include <vector>
#include "Animal.hpp"
#include "CppException.hpp"

// this file contains a series of unit tests.


//---------------------------------------------------------------------------//
// test the plant class
void test_plant()
{
  std::cout << "plant test" << std::endl;

  // make a plant.
  Plant kale("kale", .7, 2, 5000);

  // try to clone the kale and check that they have the same name.
  Organism *kale2 = kale.clone();
  if (kale2->getName() != kale.getName())
    throw CppException("Failed to create plant using Organism clone function");

  // now try the other constructor mechanism.
  Plant kale3(kale);
  if (kale3.getName() != kale.getName())
    throw CppException("Failed to create plant using Plant(plant) function");

}

//---------------------------------------------------------------------------//
// test the animal class
void test_animal()
{
  std::cout << "animal test" << std::endl;

  std::vector<std::string> food;
  food.push_back("goats");

  // make an animal.
  Animal chupacabra("chupacabra", .7,2, food);

  // try to clone the animal
  Organism *chupacabra2 = chupacabra.clone();
  if (chupacabra2->getName() != chupacabra.getName())
    throw CppException("Failed to create animal using Organism clone function");

}

//---------------------------------------------------------------------------//
// test the organism class
void test_organism()
{
  std::cout << "organism test" << std::endl;
}

//---------------------------------------------------------------------------//
// test the forest class
void test_forest()
{
  std::cout << "forest test" << std::endl;
}

//---------------------------------------------------------------------------//
// test the bounds on the Time class
void test_time()
{
  std::cout << "Time test" << std::endl;

  // try to set negative start time
  Time time_neg(-50, 10);

  // try to set end before begin time
  Time time_order(50, 10);

}

//---------------------------------------------------------------------------//
// the main program
int main()
{

  // run some tests
  try
  {
    test_plant();
    test_organism();
    test_animal();
    test_forest();
    test_time();
  }
  // catch error of type CppException
  catch (const CppException & err)
  {
    err.Report();
    return 1;
  }

  return 0;
}
