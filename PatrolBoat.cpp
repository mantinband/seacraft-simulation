//
// Created by amichai on 11/06/18.
//

#include "PatrolBoat.h"
#include "Port.h"
#include "Model.h"

PatrolBoat::PatrolBoat(const string &name, Point p, int strength)
        : Seacraft(name, p ,strength),originPort(weak_ptr<Port>()),currentlyAt(weak_ptr<Port>()) {
    setFuel(FUEL_TANK_SIZE);
}

string PatrolBoat::getStatusDetails() const {
    stringstream ss;
    ss << "Patrol_boat " << getName() << " at " << getPointString()
       << ", fuel: " << fixed << setprecision(2)
       << getFuel()/1000 << " kl, resistance: " << getStrength();


    if (getDestination().lock() != weak_ptr<Port>().lock()){
        ss << ", Moving to " << getDestination().lock()->getName()
                           << " on course " << fixed << setprecision(2) << toSeaDegree(getCourseDegree())
                           << " deg, speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    }
    return ss.str();
}

string PatrolBoat::getClassName() const {
    return "PatrolBoat";
}

void PatrolBoat::update() {
    try {
        switch (getStatus()) {
            case movingToPort:
                if (portIsInReach()){
                    setFuel(getFuel()-getDistance(getDestination().lock()->getLocation())*FUEL_CONSUMPTION);
                    setLocation(getDestination().lock()->getLocation());
                    setEndPosition(nullptr);
                    setCourseVector(nullptr);

                    /*  if cycle ended: set status to "stopped". "dockedAt" otherwise   */
                    setStatus(!visitedPorts.empty() && getDestination().lock() == originPort.lock() ? stopped : dockedAt);

                    /*  add current port to visited ports   */
                    visitedPorts.insert(getDestination().lock()->getName());

                    currentlyAt = getDestination();
                    setDestinationPort(weak_ptr<Port>());
                    numberOfHoursAtPort=0;
                } else {
                    setFuel(getFuel()-getSpeed()*FUEL_CONSUMPTION);
                    moveOnCourse(getSpeed());
                }
                break;
            case dockedAt:
                /*  if current port is the port set as docking port */
                if (currentlyAt.lock()->getName() == dockAt.lock()->getName()){
                    setStatus(stopped);
                    /*  if third hour has been reached, compute next port to visit  */
                } else if (++numberOfHoursAtPort == 3){
                    Seacraft::setDestination(Model::getInstance().getClosestPort(getLocation(), visitedPorts),getSpeed());
                    if (getDestination().lock() == weak_ptr<Port>().lock()){
                        setDestinationPort(originPort);
                        currentlyAt = weak_ptr<Port>();
                    }
                }
                break;
            case stopped:
                break;
            case deadInTheWater:
                break;
            default:
                throw unexpectedStateException();
        }
    } catch (notEnoughFuelForUpdateException &e){
        /*  if fuel is finished */
        cerr << e.what() << endl;
        setStatus(deadInTheWater);
        moveOnCourse(getFuel()/FUEL_CONSUMPTION);   /* continue until out of fuel   */
        setFuel(0);
        cerr << "status of " << getName() << " is now dead in the water" << endl;
    }
}

bool PatrolBoat::isValidSpeed(double speed) const {
    return speed >= 0 && speed <= MAX_SPEED;
}

double PatrolBoat::getMaxSpeed() const {
    return MAX_SPEED;
}

void PatrolBoat::setDestination(weak_ptr<Port> destination, double speed) {
    Seacraft::setDestination(destination, speed);
    visitedPorts.clear();
    originPort = destination;
}

double PatrolBoat::getFuelConsumption() const {
    return FUEL_CONSUMPTION;
}

void PatrolBoat::refuel(weak_ptr<Seacraft> s) {
    /*  if ships isn't in its first visit hour  */
    if (numberOfHoursAtPort != 0){
        throw invalidRefuelRequestException();
    }
    /*  if port's fuel queue is not empty   */
    if (currentlyAt.lock()->getRefuelQueueLength() > 0){
        throw refuelQueueNotEmptyException();
    }
    currentlyAt.lock()->addToRefuelQueue(shared_ptr<Seacraft>(s));
}

void PatrolBoat::setDockingPort(weak_ptr<Port> dockAt) {
    dockAt = dockAt;
}
