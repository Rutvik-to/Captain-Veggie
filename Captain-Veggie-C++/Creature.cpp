#include "Creature.h"
#include "FieldInhabitant.h"

Creature::Creature(int x, int y, string symbol) : FieldInhabitant(symbol), x_(x), y_(y) {}