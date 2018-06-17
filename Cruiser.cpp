//
// Created by amichai on 11/06/18.
//

#include "Cruiser.h"
#include "Freighter.h"
#include "PatrolBoat.h"


string Cruiser::getStatusDetails() const {
    stringstream ss;
    ss << "Cruiser " << getName() << " at "
       << getPointString() << ", force: " << getStrength();

    if (getStatus() != stopped){
        ss << ", Moving on course " << fixed << setprecision(2) << toSeaDegree(getCourseDegree())
           << " deg, speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    }
    return ss.str();
}

Cruiser::Cruiser(const string &craftName, Point point, int strength, float attackRadius)
:Seacraft(craftName,point,strength),attackRadius(attackRadius), toAttack(weak_ptr<Seacraft>()){
}

string Cruiser::getClassName() const {
    return "Cruiser";
}

void Cruiser::attack(weak_ptr<Seacraft> seacraft) {
    if (!seacraftIsInAttackRadius(seacraft)){
        throw seacraftNotInAttackRadiusException();
    }

    toAttack = seacraft;
}

bool Cruiser::seacraftIsInAttackRadius(weak_ptr<Seacraft> seacraft) {
    double distanceSquared = square(seacraft.lock()->getLocation().x- getLocation().x)
                        + square(seacraft.lock()->getLocation().y- getLocation().y);

    return distanceSquared <= square(attackRadius);
}

void Cruiser::update() {
    if (toAttack.lock() != weak_ptr<Seacraft>().lock()){
        if (getStrength() > toAttack.lock()->getStrength()){
            setStrength(getStrength()+1);
            if (toAttack.lock()->getClassName() == "Freighter"){
                dynamic_cast<Freighter*>(&*toAttack.lock())->setNumContainers(0);
            } else if (toAttack.lock()->getClassName() == "PatrolBoat"){
                setStrength(getStrength()-1);
            } else {
                throw unexpectedStateException();
            }
            toAttack.lock()->setDestinationPort(weak_ptr<Port>());
            toAttack.lock()->setSpeed(0);
            toAttack.lock()->setStatus(stopped);
        } else {
            if (toAttack.lock()->getClassName() == "PatrolBoat"){
                dynamic_cast<PatrolBoat*>(&*toAttack.lock())
                        ->setStrength(dynamic_cast<PatrolBoat*>(&*toAttack.lock())->getStrength()+1);
            }
            setStrength(getStrength()-1);
        }
    }
    moveOnCourse(getSpeed());
}

bool Cruiser::isValidSpeed(double speed) const {
    return speed >=0 && speed <= MAX_SPEED;
}

double Cruiser::getMaxSpeed() const {
    return MAX_SPEED;
}

double Cruiser::getFuelConsumption() const {
    throw fuelNotSupportedException();
}

void Cruiser::refuel(weak_ptr<Seacraft> ptr) {
    throw fuelNotSupportedException();
}

