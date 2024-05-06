#ifndef RABBIT_H
#define RABBIT_H

#include "Creature.h"
// Rabbit inherits class Creature
class Rabbit : public Creature {
public:
  // Constructor
  Rabbit(int x, int y);
};

// No setter and getter functions required as they are inherited from class Creature

#endif
