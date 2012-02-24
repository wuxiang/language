#include "Organism.hpp"
#include <iostream>
#include <list>
#include "Time.hpp"
#include "Forest.hpp"
#include "Plant.hpp"
#include <vector>
#include "Animal.hpp"

int main()
{

  const int YEAR = 12;

  Forest forest;

  Plant grass("grass", 0.9, 6, 3000);

  std::vector<std::string> food;
  food.push_back("grass");
  Animal rabbit("rabbit", 1.05/YEAR, YEAR, food);


  int i;
  for(i = 0; i < 1000; i++) forest.addOrganism(grass);
  for(i = 0; i < 500; i++)  forest.addOrganism(rabbit);

  Time time(0, 200);
  while(time.step(forest)) {
    std::cout << "Time:    " << time.getTime() << "\t"
	      << "Rabbits: " << forest.getPopulation("rabbit") << "\t"
	      << "Grasses: " << forest.getPopulation("grass")  << std::endl;
  }

  return 0;
}
