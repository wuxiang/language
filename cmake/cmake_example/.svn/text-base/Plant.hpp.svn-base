//Plant.hpp

#ifndef _PLANT_HPP_
#define _PLANT_HPP_

#include "Organism.hpp"

class Plant : public Organism {

private :
  
public :

  Plant(const Plant& plant);

  Plant(const std::string& name, double rep, int maxage, int maxnum);

  // maxNum is the maximum number of plants
  int maxNum;

  virtual void specialAdvance(Forest& forest);

  Organism* clone() const { return new Plant(*this); }

};

#endif
