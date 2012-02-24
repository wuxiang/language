#include "Forest.hpp"


void Forest::kill()
{
  std::vector<std::string>::iterator iter;
  std::list<Organism*>::iterator org;

  for(iter = killVec.begin(); iter != killVec.end(); iter++) {

    for(org = ecosystem.begin(); org != ecosystem.end(); org++) {
      
      if( *iter == (*org)->getName() ) {
	removeOrganism(org);
	break;
      }      
    }
  }  

  killVec.clear();
}
