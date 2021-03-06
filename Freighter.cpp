//
// Created by amichai on 11/06/18.
//

#include <cmath>
#include "Freighter.h"
#include "Port.h"
RegisterSeacraft Freighter::registerSeacraft("Freighter",createFreighter);

Freighter::Freighter(const string &name, Point p, int strength, int containers)
        : Seacraft(name, p, strength) ,maxContainers(containers),numContainers(0){
    setFuel(FUEL_TANK_SIZE);
    loadAt = weak_ptr<Port>();
    unloadAt = weak_ptr<Port>();
    currentlyAt = weak_ptr<Port>();
}

string Freighter::getStatusDetails() const {
    stringstream ss;
    ss << "Freighter " << getName() << " at " << getPointString()
            << ", fuel: " << fixed << setprecision(2) << getFuel()/1000
            << " kl, resistance: " << getStrength();

    if (getStatus() != stopped && getStatus() != dockedAt && getStatus() != deadInTheWater ){
        ss << ", Moving";
        if (getStatus() != movingOnCourse) {
            switch (getStatus()) {
                case movingToPort:
                    ss << " to " << getDestination().lock()->getName();
                    break;
                case movingToPosition:
                    ss << " to " << getEndPosition().toString();
                    break;
                default:
                    throw unexpectedStateException();
            }
        }
        ss << " on course " << fixed << setprecision(2) << toSeaDegree(getCourseDegree())
                            << " deg, speed " << fixed << setprecision(2) << getSpeed() << " nm/hr";
    } else if (getStatus() == dockedAt){
        ss << " docked at: " << currentlyAt.lock()->getName();
    }

    ss << ", containers: " << numContainers;

    if (getStatus() == movingToPort){
        if (loadAt.lock() != weak_ptr<Port>().lock() && getDestination().lock()->getName() == loadAt.lock()->getName()) {
            ss << ", moving to loading destination";
        } else if (unloadAt.lock() != weak_ptr<Port>().lock() && getDestination().lock()->getName() == unloadAt.lock()->getName()){
            ss << ", moving to unloading destination";
        }
    }

    if (loadAt.lock() == weak_ptr<Port>().lock() &&
            unloadAt.lock() == weak_ptr<Port>().lock()){
        ss << ", no cargo destinations";
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

void Freighter::setUnloadAt(weak_ptr<Port> unloadAt, int numOfContainersToUnload) {
    if (loadAt.lock() != weak_ptr<Port>().lock() && loadAt.lock()->getName() == unloadAt.lock()->getName()){
        throw invalidUnloadingPortException();
    }
    this->unloadAt = unloadAt;
    this->numContainersToUnload = numOfContainersToUnload;
}

void Freighter::setDockingPort(weak_ptr<Port> dockAt) {
    this->dockAt = dockAt;
}

void Freighter::refuel(weak_ptr<Seacraft> s) {
    if (getStatus() != dockedAt){
        throw invalidRefuelRequestException();
    }

    currentlyAt.lock()->addToRefuelQueue(shared_ptr<Seacraft>(s));
}

void Freighter::update() {
    try {
        switch (getStatus()) {
            case movingToPosition:
                if (positionIsInReach()) {
                    setFuel(getFuel()-getDistance(getEndPosition())*FUEL_CONSUMPTION);
                    setLocation(getEndPosition());
                    setSpeed(0);
                    setEndPosition(nullptr);
                    setCourseVector(nullptr);
                    setStatus(stopped);
                } else {
                    setFuel(getFuel()-getSpeed()*FUEL_CONSUMPTION);
                    moveOnCourse(getSpeed());
                }
                break;
            case movingToPort:
                if (portIsInReach()) {
                    setFuel(getFuel()-getDistance(getDestination().lock()->getLocation())*FUEL_CONSUMPTION);
                    setLocation(getDestination().lock()->getLocation());
                    setSpeed(0);
                    setEndPosition(nullptr);
                    setCourseVector(nullptr);
                    setStatus(dockedAt);
                    currentlyAt = getDestination();
                    setDestinationPort(weak_ptr<Port>());
                } else {
                    setFuel(getFuel()-getSpeed()*FUEL_CONSUMPTION);
                    moveOnCourse(getSpeed());
                }
                break;
            case movingOnCourse:
                if (!enoughFuelForUpdate()){
                    throw notEnoughFuelForUpdateException();
                }
                moveOnCourse(getSpeed());
                break;
            case dockedAt:
                if (loadAt.lock() == currentlyAt.lock()){
                    numContainers = maxContainers;
                    loadAt = weak_ptr<Port>();
                } else if (unloadAt.lock() == currentlyAt.lock()){
                    numContainers -= numContainersToUnload;
                    unloadAt = weak_ptr<Port>();
                    if (numContainers < 0){
                        throw notEnoughContainersToUnloadException();
                    }
                }
                break;
            case stopped:
                return;
            case deadInTheWater:
                return;
        }
    } catch (notEnoughFuelForUpdateException &e){
        cerr << e.what() << endl;
        setStatus(deadInTheWater);
        moveOnCourse(getFuel()/FUEL_CONSUMPTION);   /* continue until out of fuel   */
        setFuel(0);
        cerr << "status of " << getName() << " is now dead in the water" << endl;
    } catch (notEnoughContainersToUnloadException &e){
        cerr << e.what() << endl;
        numContainers = 0;
    }
}



bool Freighter::isValidSpeed(double speed) const {
    return speed >= 0 && speed <= MAX_SPEED;
}

double Freighter::getMaxSpeed() const {
    return MAX_SPEED;
}


void Freighter::setCourse(double degree, double speed) {
    Seacraft::setCourse(degree, speed);
    currentlyAt = weak_ptr<Port>();
}

void Freighter::setPosition(Point point, double speed) {
    Seacraft::setPosition(point, speed);
    currentlyAt = weak_ptr<Port>();
}

void Freighter::setDestination(weak_ptr<Port> destination, double speed) {
    Seacraft::setDestination(destination, speed);
    currentlyAt = weak_ptr<Port>();
}

double Freighter::getFuelConsumption() const {
    return FUEL_CONSUMPTION;
}

void Freighter::setNumContainers(int numContainers) {
    Freighter::numContainers = numContainers;
}

shared_ptr<Seacraft> Freighter::createFreighter(const string &data) {
    string name;
    Point p;
    int strength;
    int containers = 0;

    stringstream ss;
    ss << data;
    ss >> name >> p.x >> p.y >> strength;
    if (ss.rdbuf()->in_avail() > 1){
        ss >> containers;
        return shared_ptr<Seacraft>(new Freighter(name,p,strength,containers));
    }

    return shared_ptr<Seacraft>(new Freighter(name,p,strength));
}

Freighter::Freighter(const Freighter &rhs) : Seacraft(rhs) {
    maxContainers = rhs.getMaxContainers();
    numContainers = rhs.getNumContainers();
    loadAt = rhs.getLoadAt();
    dockAt = rhs.getDockAt();
    unloadAt = rhs.getUnloadAt();
    currentlyAt = rhs.getCurrentlyAt();
    numContainersToUnload = rhs.getNumContainersToUnload();
}

int Freighter::getMaxContainers() const {
    return maxContainers;
}

int Freighter::getNumContainers() const {
    return numContainers;
}

const weak_ptr<Port> &Freighter::getLoadAt() const {
    return loadAt;
}

const weak_ptr<Port> &Freighter::getDockAt() const {
    return dockAt;
}

const weak_ptr<Port> &Freighter::getUnloadAt() const {
    return unloadAt;
}

const weak_ptr<Port> &Freighter::getCurrentlyAt() const {
    return currentlyAt;
}

int Freighter::getNumContainersToUnload() const {
    return numContainersToUnload;
}

Freighter &Freighter::operator=(const Freighter &rhs) {
    Seacraft::operator=(rhs);

    maxContainers = rhs.getMaxContainers();
    numContainers = rhs.getNumContainers();
    loadAt = rhs.getLoadAt();
    dockAt = rhs.getDockAt();
    unloadAt = rhs.getUnloadAt();
    currentlyAt = rhs.getCurrentlyAt();
    numContainersToUnload = rhs.getNumContainersToUnload();

    return *this;
}

Freighter::Freighter(Freighter &&rhs) noexcept : Seacraft(move(rhs)){
    maxContainers = rhs.getMaxContainers();
    numContainers = rhs.getNumContainers();
    loadAt = rhs.getLoadAt();
    dockAt = rhs.getDockAt();
    unloadAt = rhs.getUnloadAt();
    currentlyAt = rhs.getCurrentlyAt();
    numContainersToUnload = rhs.getNumContainersToUnload();

    rhs.setMaxContainers(0);
    rhs.setNumContainers(0);
    rhs.setLoadAt(weak_ptr<Port>());
    rhs.setDockingPort(weak_ptr<Port>());
    rhs.setUnloadAt(weak_ptr<Port>(),0);
    rhs.setCurrentlyAt(weak_ptr<Port>());
}

void Freighter::setMaxContainers(int maxContainers) {
    Freighter::maxContainers = maxContainers;
}

void Freighter::setCurrentlyAt(const weak_ptr<Port> &currentlyAt) {
    Freighter::currentlyAt = currentlyAt;
}

Freighter &Freighter::operator=(Freighter &&rhs) noexcept {
    maxContainers = rhs.getMaxContainers();
    numContainers = rhs.getNumContainers();
    loadAt = rhs.getLoadAt();
    dockAt = rhs.getDockAt();
    unloadAt = rhs.getUnloadAt();
    currentlyAt = rhs.getCurrentlyAt();
    numContainersToUnload = rhs.getNumContainersToUnload();

    rhs.setMaxContainers(0);
    rhs.setNumContainers(0);
    rhs.setLoadAt(weak_ptr<Port>());
    rhs.setDockingPort(weak_ptr<Port>());
    rhs.setUnloadAt(weak_ptr<Port>(),0);
    rhs.setCurrentlyAt(weak_ptr<Port>());

    Seacraft::operator=(move(rhs));
    return *this;
}


