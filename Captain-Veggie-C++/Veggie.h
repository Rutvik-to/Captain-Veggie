#ifndef VEGGIE_H
#define VEGGIE_H

// Inherit from class FieldInhabitant
#include "FieldInhabitant.h"

class Veggie : public FieldInhabitant {

// Define private variables such as name and points
private:
string name_;
int points_;

public:
// Constructor to initialize name, symbol, and points
Veggie(string& name, string& symbol, int points);

// Getter functions for name and points
string& getName() {
    return name_;
}

int getPoints() {
    return points_; 
}

// Virtual Destructor function
virtual ~Veggie() = default;
};

#endif