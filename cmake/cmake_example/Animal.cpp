#include "Animal.hpp"


void Animal::specialAdvance(Forest& forest)
{
  int nfood = 0;
    
  for(size_t i = 0; i < food.size(); i++) {
    nfood += forest.getPopulation(food[i]);
  }

  int popi = forest.getPopulation(name);
  if(popi > nfood) {

    double popd = popi;
    if(rand()/static_cast<double>(RAND_MAX) > nfood/popd) {
      die = true;
      return;
    }
  }

  eatSomething(forest, nfood);
  
}


void Animal::eatSomething(Forest& forest, int nfood) const
{
  double total = 0;
  double r = rand() / static_cast<double>(RAND_MAX);

  for(int i = 0; i < food.size(); i++) {
    total += forest.getPopulation(food[i]);
    if(r < total) {
      forest.kill(food[i]);
      return;
    }
  }
}
