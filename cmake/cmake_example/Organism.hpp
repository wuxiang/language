// Organism.hpp

#ifndef _ORGANISM_HPP_
#define _ORGANISM_HPP_

#include <string>

class Forest; 

class Organism
{

protected:
	
  double reproProb;

  int maxAge;

  int age; 
 
  std::string name;

  bool die;

  bool repr;

public:

  bool shouldDie() { return die; }

  bool shouldRepr() { return repr; }

  Organism(const std::string& n, double rProb, int max);

  Organism(const Organism& org);

  void advance(Forest& forest);

  virtual void specialAdvance(Forest& forest) = 0;

  const std::string& getName() const {return name;}

  virtual Organism* clone() const = 0;

};

#endif
