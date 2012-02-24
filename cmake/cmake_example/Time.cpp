// Time.cpp

#include "Time.hpp"
#include "Forest.hpp"
#include <iostream>
#include "CppException.hpp"

Time::Time(int start, int end)
{
  // Initialize the various times
  t0 = start;
  tf = end;
  t = start;
}

bool Time::step(Forest &forest)
{
  std::list<Organism*>::iterator iter;
  
  // Loop over all of the organisms:
  for(iter = forest.ecosystem.begin(); iter != forest.ecosystem.end(); iter++) {
    (*iter)->advance(forest);
  }

  for(iter = forest.ecosystem.begin(); iter != forest.ecosystem.end();) {

    // Deal with reproduction:
    if( (*iter)->shouldRepr() ) forest.addOrganism(**iter);

    // Kill the organism if necessary:
    if( (*iter)->shouldDie() ) {
      forest.removeOrganism(iter);
    } else {
      iter++;
    }
  }

  // Kill any additional organisms:
  forest.kill();

  t++;
  return t < tf;
}
