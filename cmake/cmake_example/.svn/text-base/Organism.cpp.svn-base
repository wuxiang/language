// Organism.cpp
#include <cstdlib>
#include "Organism.hpp"

Organism::Organism(const std::string& n, double rProb, int max)
{
  die = false;
  repr = false;
  name = n;
  reproProb = rProb;
  maxAge = max;
  age = 0;
}

void Organism::advance(Forest& forest)
{
  // No dying!
  die = false;
  repr = false;

  // if we're too old, die:
  if(age == maxAge) {
    die = true;
    return;
  }

  // figure out if we reproduce

  // get a double between 0 and 1, make sure to avoid integer divition:
  double randNum = rand() / (static_cast<double>(RAND_MAX));

  if (randNum < reproProb) {
    // We've successfully reproduced:
    repr = true;
  }  

  // we can also die through some species-specific mechanism
  specialAdvance(forest);
  if(die) {
    // We're dead and do not reproduce:
    repr = false;
    die = true;
    return;
  }

  // We've survied, so we are one month older:
  age ++;
}

Organism::Organism(const Organism& org)
{
  name = org.name;
  reproProb = org.reproProb;
  maxAge = org.maxAge;
  age = 0;
  die = false;
  repr = false;
}
