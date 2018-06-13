//
// Created by amichai on 11/06/18.
//

#include "Cruiser.h"

Cruiser::Cruiser(const string &name, Point p, int strength) :
        Seacraft(name, p, strength) {}

string Cruiser::getStatus() const {
    return "Cruiser " + getName() + " at position " + getPointString() + ", force: " + to_string(getStrength()); //TODO: ADD DEGREE AND SPEED
}
