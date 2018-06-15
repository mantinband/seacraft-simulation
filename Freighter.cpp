//
// Created by amichai on 11/06/18.
//

#include "Freighter.h"
#include "Port.h"
Freighter::Freighter(const string &name, Point p, int strength, int containers)
        : Seacraft(name, p, strength) ,containers(containers){
    setFuel(FUEL_TANK_SIZE);
}

string Freighter::getStatus() const {
    stringstream ss;
    ss << "Freighter " << getName() << " at " << getPointString()
            << ", fuel: " << fixed << setprecision(2) << getFuel()
            << " kl, resistance: " << getStrength();

    if (getDestination().lock() != weak_ptr<Port>().lock()){
        ss << " Moving to " << getDestination().lock()->getName()
                            << " on course " << fixed << setprecision(2) << getCourseDegree()
                            << " speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    }
    ss << " containers: " << to_string(containers);
    return ss.str(); //TODO: ADD DESTINATION & SPEED;
}
