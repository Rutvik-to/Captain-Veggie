#include "Captain.h"


Captain::Captain(int x, int y) : Creature(x, y, "V") {}

// Function definations
void Captain::addVeggie(Veggie* veggie) {
collectedVeggies.push_back(veggie);
}

Captain::~Captain() {
// Destructor should clear the collected veggies vector
for (Veggie* veggie : collectedVeggies) {
delete veggie;
}
collectedVeggies.clear();
}