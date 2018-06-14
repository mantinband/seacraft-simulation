//
// Created by amichai on 11/06/18.
//

#include "Freighter.h"

Freighter::Freighter(const string &name, Point p, int strength, int containers)
        : Seacraft(name, p, strength) ,containers(containers){
    setFuel(FUEL_TANK_SIZE);
}

string Freighter::getStatus() const {
    stringstream ss;
    ss << "Freighter " << getName() << " at position " << getPointString()
            << ", fuel: " << fixed << setprecision(2) << getFuel()
            << ", resistance: " << getStrength()
            << " containers: " << to_string(containers);
    return ss.str(); //TODO: ADD DESTINATION & SPEED;
}
