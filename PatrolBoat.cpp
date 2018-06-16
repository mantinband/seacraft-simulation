//
// Created by amichai on 11/06/18.
//

#include "PatrolBoat.h"
#include "Port.h"

PatrolBoat::PatrolBoat(const string &name, Point p, int strength)
        : Seacraft(name, p ,strength) {
    setFuel(FUEL_TANK_SIZE);
}

string PatrolBoat::getStatusDetails() const {
    stringstream ss;
    ss << "Patrol_boat " << getName() << " at " << getPointString()
       << ", fuel: " << fixed << setprecision(2)
       << getFuel()/1000 << " resistance: " << getStrength();


    if (getDestination().lock() != weak_ptr<Port>().lock()){
        ss << ", Moving to " << getDestination().lock()->getName()
                           << " on course " << fixed << setprecision(2) << getCourseDegree()
                           << " deg, speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    }
    return ss.str(); //TODO: add destinationPort etc'
}

string PatrolBoat::getClassName() const {
    return "PatrolBoat";
}

void PatrolBoat::update() {

}

bool PatrolBoat::isValidSpeed(double speed) const {
    return speed >= 0 && speed <= MAX_SPEED;
}

double PatrolBoat::getMaxSpeed() const {
    return MAX_SPEED;
}
