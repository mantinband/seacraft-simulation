//
// Created by amichai on 11/06/18.
//

#include "Cruiser.h"

Cruiser::Cruiser(const string &name, Point p, int strength) :
        Seacraft(name, p, strength) {}

string Cruiser::getStatus() const {
    stringstream ss;
    ss << "Cruiser " << getName() << " at position "
       << getPointString() << ", force: " << getStrength();
    return ss.str(); //TODO: ADD DEGREE, SPEED, COURSE
}

Cruiser::Cruiser(const string &craftName, Point point, int strength, float attackRadius)
:Seacraft(craftName,point,strength) {
    this->attackRadius = attackRadius;
}
