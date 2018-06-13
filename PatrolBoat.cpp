//
// Created by amichai on 11/06/18.
//

#include "PatrolBoat.h"

PatrolBoat::PatrolBoat(const string &name, Point p, int strength)
        : Seacraft(name, p ,strength) {
    setFuel(FUEL_TANK_SIZE);
}

string PatrolBoat::getStatus() const {
    return "Patrol_boat " + getName() + " at " + getPointString() + ", fuel: "
           + to_string(getFuel()) + " resistance: " + to_string(getStrength()); //TODO: add moving to destination and speed
}
