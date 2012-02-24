// Time.cpp

#include "Time.hpp"
#include "Forest.hpp"
#include <iostream>
#include "CppException.hpp"

Time::Time(int start, int end)
{

  // Check that sensible times were entered
  // First check that the start time is non-negative. Note that we don't need to check
  // that the end time is non-negative because that case will be caught be one of these
  // two tests.
  if (start < 0)
  {
    throw CppException("Error: start time is negative; enter a start time >= 0.");
  }

  // Check that the end time is not before the start time.
  if (end < start)
  {
    throw CppException("Error: can't go backwards in time, make end time after start time.");
  }

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
