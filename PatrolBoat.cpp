//
// Created by amichai on 11/06/18.
//

#include "PatrolBoat.h"
#include "Port.h"

PatrolBoat::PatrolBoat(const string &name, Point p, int strength)
        : Seacraft(name, p ,strength) {
    setFuel(FUEL_TANK_SIZE);
}

string PatrolBoat::getStatus() const {
    stringstream ss;
    ss << "Patrol_boat " << getName() << " at " << getPointString()
       << ", fuel: " << fixed << setprecision(2)
       << getFuel() << " resistance: " << getStrength();


    if (getDestination().lock() != weak_ptr<Port>().lock()){
        ss << "Moving to " << getDestination().lock()->getName()
                           << " on course " << fixed << setprecision(2) << getCourseDegree()
                           << " speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    }
    return ss.str(); //TODO: add destination etc'
}
