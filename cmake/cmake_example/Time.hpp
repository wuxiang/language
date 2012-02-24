// Time.hpp

#ifndef _TIME_HPP_
#define _TIME_HPP_

#include "Organism.hpp"
#include <list>

class Forest;

class Time
{

private:

  int t0;

  int tf;
 
  int t;

public:
	
  Time(int start, int end);

  bool step(Forest &forest);

  int getTime() {return t;}

};

#endif
