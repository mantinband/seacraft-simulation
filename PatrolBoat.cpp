//
// Created by amichai on 11/06/18.
//

#include "PatrolBoat.h"

PatrolBoat::PatrolBoat(const string &name, Point p, int strength)
        : Seacraft(name, p ,strength) {
    setFuel(FUEL_TANK_SIZE);
}

string PatrolBoat::getStatus() const {
    stringstream ss;
    ss << "Patrol_boat " << getName() << " at " << getPointString()
       << ", fuel: " << fixed << setprecision(2)
       << getFuel() << " resistance: " << getStrength();
    return ss.str(); //TODO: add moving to destination and speed
}
