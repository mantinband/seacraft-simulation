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
    /*  if seacraft is out of reach */
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
    /*  if there is a pending attack request    */
    if (toAttack.lock() != weak_ptr<Seacraft>().lock()){
        /*  if the pirate-ship has more strength    */
        if (getStrength() > toAttack.lock()->getStrength()){
            /*  pirate-ship's strength++*/
            setStrength(getStrength()+1);
            /*  if attacked ship is freighter, empty it's containers    */
            if (toAttack.lock()->getClassName() == "Freighter"){
                dynamic_cast<Freighter*>(&*toAttack.lock())->setNumContainers(0);
                /*  if its a patrol boat, patrol boat's strength--  */
            } else if (toAttack.lock()->getClassName() == "PatrolBoat"){
                setStrength(getStrength()-1);
            } else {
                throw unexpectedStateException();
            }
            /*  stop attacked ship  */
            toAttack.lock()->setDestinationPort(weak_ptr<Port>());
            toAttack.lock()->setSpeed(0);
            toAttack.lock()->setStatus(stopped);
        } else {
            /*  if attack failed & the attacked ship is a patrol boat,
             *  patrol boat's strength++ */
            if (toAttack.lock()->getClassName() == "PatrolBoat"){
                dynamic_cast<PatrolBoat*>(&*toAttack.lock())
                        ->setStrength(dynamic_cast<PatrolBoat*>(&*toAttack.lock())->getStrength()+1);
            }
            /*  if attack failed, pirate ship's strength--  */
            setStrength(getStrength()-1);
        }
        /*  dismiss attack request */
        toAttack = weak_ptr<Seacraft>();
    }
    /*  continue sailing    */
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

