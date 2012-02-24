#ifndef _ANIMAL_HPP_
#define _ANIMAL_HPP_

#include <cstdlib>

#include "Organism.hpp"
#include "Forest.hpp"

class Animal : public Organism {

private :
  std::vector<std::string> food;
  
  /**
  * when eatSomething is called, one of the foods in 
  * the forest is killed for every animal of my type.
  * @param forest the forest in which the animal lives
  * @param nfood the food index number that is eaten
  */
  void eatSomething(Forest& forest, int nfood) const;
  
public :
  Animal(const Animal& animal) :
    Organism(animal), food(animal.food)
  {

  }

  Animal(const std::string& name, double rep, int maxage, 
   const std::vector<std::string>& afood) :
    Organism(name, rep, maxage), food(afood)
  {
    
  }

  virtual void specialAdvance(Forest& forest);

  Organism* clone() const { return new Animal(*this); }


};

#endif
