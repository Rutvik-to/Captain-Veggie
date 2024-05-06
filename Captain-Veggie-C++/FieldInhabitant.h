#ifndef FIELDINHABITANT_H
#define FIELDINHABITANT_H

#include <string>
using namespace std;

// Defining class FieldInhabitant
class FieldInhabitant {

// Defining Private variables
private:
string Character;

// Defining Protected Variables and functions
protected:
// Constructor to initialize the symbol
FieldInhabitant(string& symbol);

// Defining Public variables
public:

// Getter and setter functions for symbol
string& getSymbol() {
    return Character; 
}

void setSymbol(string& symbol) {
     Character = symbol;
}

// Virtual destructor
virtual ~FieldInhabitant() = default;
};

#endif