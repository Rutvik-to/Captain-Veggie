#include "Veggie.h"
#include "FieldInhabitant.h"

Veggie::Veggie(string& name, string& symbol, int points) : FieldInhabitant(symbol), name_(name), points_(points) {}