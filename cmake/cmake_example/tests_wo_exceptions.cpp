#include "Organism.hpp"
#include <iostream>
#include <list>
#include "Time.hpp"
#include "Forest.hpp"
#include "Plant.hpp"
#include <vector>
#include "Animal.hpp"

// this file contains a series of tests, both unit tests and integrated system tests.
//---------------------------------------------------------------------------//
// test the plant class
int test_plant(int count)
{
	std::cout << "plant test" << std::endl;

	// make a plant.
	Plant kale("kale", .7, 2, 5000);

	// try to clone the kale and check that they have the same name.
	Organism *kale2 = kale.clone();
	if (kale2->getName() != kale.getName()) ++count;

	// now try the other constructor mechanism.
	Plant kale3(kale);
	if (kale3.getName() != kale.getName()) ++count;

	return count;
}

//---------------------------------------------------------------------------//
// test the animal class
int test_animal(int count)
{
	std::cout << "animal test" << std::endl;
  std::vector<std::string> food;
  food.push_back("goats");

  // make an animal. 
  Animal chupacabra("chupacabra", .7,2, food);
  
  // try to clone the animal
	Organism *chupacabra2 = chupacabra.clone();
	if (chupacabra2->getName() != chupacabra.getName()) ++count;


	return count;
}

//---------------------------------------------------------------------------//
// test the organism class
int test_organism(int count)
{
	std::cout << "organism test" << std::endl;

	return count;
}

//---------------------------------------------------------------------------//
// test the forest class
int test_forest(int count)
{
	std::cout << "forest test" << std::endl;

	return count;
}

//
int main()
{

  int err_count = 0;

  // run some tests
  err_count = test_organism(err_count);
  err_count = test_plant(err_count);
  err_count = test_animal(err_count);
  err_count = test_forest(err_count);

  std::cout << "number of errors: " << err_count << std::endl;

  return err_count;
}
