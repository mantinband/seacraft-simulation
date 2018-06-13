//
// Created by amichai on 11/06/18.
//

#include "Freighter.h"

Freighter::Freighter(const string &name, Point p, int strength, int containers)
        : Seacraft(name, p, strength) ,containers(containers){
    setFuel(FUEL_TANK_SIZE);
}

string Freighter::getStatus() const {
    return "Freighter " + getName() + " at position " + getPointString() + ", resistance: " + to_string(getStrength()) + " containers: " + to_string(containers); //TODO: ADD DESTINATION, SPEED, ;
}
