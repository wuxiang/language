// Plant.cpp

#include <cstdlib>

#include "Plant.hpp"
#include "Forest.hpp"

void Plant::specialAdvance(Forest& forest)
{
  int pop = forest.getPopulation(name);

  if(pop > maxNum) {

    double r = rand()/static_cast<double>(RAND_MAX);
    if(r  < (pop-maxNum)/static_cast<double>(maxNum)) {
      repr = false;
    }
  }
}

Plant::Plant(const Plant& plant) :
  Organism(plant), maxNum(plant.maxNum)
{

}

Plant::Plant(const std::string& name, double rep, int maxage, int maxnum) :
  Organism(name, rep, maxage), maxNum(maxnum)
{

}
