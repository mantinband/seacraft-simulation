//
// Created by amichai on 11/06/18.
//

#include "Cruiser.h"


string Cruiser::getStatusDetails() const {
    stringstream ss;
    ss << "Cruiser " << getName() << " at position "
       << getPointString() << ", force: " << getStrength();

    if (getStatus() != stopped){
        ss << ", Moving on course " << fixed << setprecision(2) << getCourseDegree()
           << " deg, speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    }
    return ss.str();
}

Cruiser::Cruiser(const string &craftName, Point point, int strength, float attackRadius)
:Seacraft(craftName,point,strength) {
    this->attackRadius = attackRadius;
}

string Cruiser::getClassName() const {
    return "Cruiser";
}
