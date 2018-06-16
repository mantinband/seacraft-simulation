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

}

bool Cruiser::isValidSpeed(double speed) const {
    return speed >=0 && speed <= MAX_SPEED;
}

double Cruiser::getMaxSpeed() const {
    return MAX_SPEED;
}

