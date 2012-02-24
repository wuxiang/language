#include "Organism.hpp"
#include <iostream>
#include "Plant.hpp"
#include "CppException.hpp"

//---------------------------------------------------------------------------//
// test the plant class
void test_plant_1()
{
  std::cout << "*** plant test 1 ***" << std::endl;

  // make a plant.
  Plant kale("kale", .7, 2, 5000);

  // try to clone the kale and check that they have the same name.
  Organism *kale2 = kale.clone();
  if (kale2->getName() != kale.getName())
    //throw &kale;
    throw CppException("Failed to create plant using Organism clone function");

}

//---------------------------------------------------------------------------//
void test_plant_2()
{
  std::cout << "*** plant test 2 ***" << std::endl;

  // make a plant.
  Plant kale("kale", .7, 2, 5000);

  // now try the other constructor mechanism.
  Plant kale3(kale);
  if (kale3.getName() != kale.getName())
    //throw &kale3;
    throw CppException("Failed to create plant using Plant(plant) function");
}

//---------------------------------------------------------------------------//
// the main program
int main()
{
  try
  {
    test_plant_1();
    test_plant_2();
  }
  // catch error of type CppException
  catch (const CppException & err)
  {
    err.Report();
    return 1;
  }

  return 0;
}
