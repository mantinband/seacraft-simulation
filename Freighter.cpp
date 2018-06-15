//
// Created by amichai on 11/06/18.
//

#include "Freighter.h"

#include <utility>
#include "Port.h"
Freighter::Freighter(const string &name, Point p, int strength, int containers)
        : Seacraft(name, p, strength) ,containers(containers){
    setFuel(FUEL_TANK_SIZE);
    loadAt = weak_ptr<Port>();
    unloadAt = weak_ptr<Port>();
}

string Freighter::getStatusDetails() const {
    stringstream ss;
    ss << "Freighter " << getName() << " at " << getPointString()
            << ", fuel: " << fixed << setprecision(2) << getFuel()
            << " kl, resistance: " << getStrength();

    if (getStatus() != stopped && getStatus() != dockedAt && getStatus() != deadInTheWater){
        ss << ", Moving";
        switch (getStatus()){
            case movingToPort:
                ss << " to " << getDestination().lock()->getName();
                break;
            case movingToPosition:
                ss << " to " << getEndPosition().toString();
                break;
            default:
                throw unexpectedStateException();
        }
        ss << " on course " << fixed << setprecision(2) << getCourseDegree()
                            << " speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    } else if (getStatus() == dockedAt){
        ss << " docked at: " << getDestination().lock()->getName();
    }

    ss << ", containers: " << containers;

    if (getStatus() == movingToPort){
        if (loadAt.lock() != weak_ptr<Port>().lock() && getDestination().lock()->getName() == loadAt.lock()->getName()) {
            ss << ", moving to loading destination";
        } else if (unloadAt.lock() != weak_ptr<Port>().lock() && getDestination().lock()->getName() == unloadAt.lock()->getName()){
            ss << ", moving to unloading destination";
        }
    }
    return ss.str();
}

string Freighter::getClassName() const {
    return "Freighter";
}

void Freighter::setLoadAt(weak_ptr<Port> loadAt) {
    if (unloadAt.lock() != weak_ptr<Port>().lock() && unloadAt.lock()->getName() == loadAt.lock()->getName()){
        throw invalidLoadingPortException();
    }
    this->loadAt = loadAt;
}

void Freighter::setUnloadAt(weak_ptr<Port> unloadAt) {
    if (loadAt.lock() != weak_ptr<Port>().lock() && loadAt.lock()->getName() == unloadAt.lock()->getName()){
        throw invalidUnloadingPortException();
    }
    this->loadAt = unloadAt;
}
