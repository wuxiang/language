#ifndef _FOREST_HPP_
#define _FOREST_HPP_

#include <list>
#include <map>
#include <vector>

#include "Organism.hpp"

class Forest
{
public:

  /**  
    * This function kills animals or plants with the name str
    * @ param str is the name
    */
  void kill(const std::string& str) {
    killVec.push_back(str);
  }

  void kill();

  std::list<Organism*> ecosystem;

  void addOrganism(const Organism& org) {
    Organism *p = org.clone();
    ecosystem.push_back(p);
    population[org.getName()]++;
  }

  void removeOrganism(std::list<Organism*>::iterator &iter) {
    delete *iter;
    population[(*iter)->getName()]--;
    iter = ecosystem.erase(iter);
  }

  int getPopulation(const std::string& name) const {
    return population.find(name)->second;
  }

  int getPopulation() const { 
    return ecosystem.size(); 
  }

private:

  std::map<std::string, int> population;

  std::vector<std::string> killVec;
};

#endif
