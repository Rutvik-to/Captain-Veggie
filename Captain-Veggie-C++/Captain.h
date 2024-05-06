#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <vector>
#include "Creature.h"
#include "Veggie.h"

// captain inherits class creature
class Captain : public Creature {
public:
  // Constructor for class captain
  Captain(int x, int y);

  // Add a Veggie object to the collected items
  void addVeggie(Veggie* veggie);
  
  // No setter and getter functions needed as they are inherited from Class Creature

  // getVeggies returns collected veggies vector
  vector<Veggie*>& getVeggies() {return collectedVeggies;}

  //destructor
  virtual ~Captain();

private:
  // Vector to store collected Veggie objects
  vector<Veggie*> collectedVeggies;
};

#endif
