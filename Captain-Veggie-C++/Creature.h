#ifndef CREATURE_H
#define CREATURE_H

// Inherit from class FieldInhabitant
#include "FieldInhabitant.h"

class Creature : public FieldInhabitant {

// define private variables
private:
int x_;
int y_;

// define public functions
public:
// Constructor to initialize x, y, and symbol
Creature(int x, int y, string symbol);

// Getter and setter functions for x and y coordinates
int getX() {
    return x_;
}

void setX(int x) {
    x_ = x;
}

int getY() {
    return y_;
}

void setY(int y) {
    y_ = y;
}

//Virtual Destructor 
virtual ~Creature() = default;
};

#endif