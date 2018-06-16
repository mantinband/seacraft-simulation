//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"
#include "Port.h"

#include <utility>
#include <cmath>

Seacraft::Seacraft(string name, Point p, int strength)
: SeaObject(std::move(name),p),strength(strength)
        ,status(stopped),destinationPort(weak_ptr<Port>()),courseVector(nullptr){
}

string Seacraft::toString() const {
    return getName() + " (" + to_string(getLocation().x) + "," + to_string(getLocation().y) + ")" + " strength: " + to_string(strength);
}



int Seacraft::getStrength() const {
    return strength;
}

void Seacraft::setCourse(double degree, double speed) {
    if (speed < 0){
        throw invalidSpeedException();
    }
    courseDegree = degree;
    this->speed = speed;
    courseVector = nullptr;
    status = movingOnCourse;
}

void Seacraft::setPosition(Point point, double speed) {
    this->speed = speed;
    endPosition = make_shared<Point>(point.x,point.y);
    courseVector = make_shared<Cartesian_vector>();
    courseVector->delta_x = point.x- getLocation().x;
    courseVector->delta_y = point.y- getLocation().y;

    courseDegree = to_degrees(Polar_vector(*courseVector).theta);
    status = movingToPosition;
}

double Seacraft::getCourseDegree() const {
    return courseDegree;
}

double Seacraft::getSpeed() const {
    return speed;
}

weak_ptr<Port> Seacraft::getDestination() const {
    return destinationPort;
}

const shared_ptr<Cartesian_vector> &Seacraft::getCourseVector() const {
    return courseVector;
}


void Seacraft::setDestination(weak_ptr<Port> destination, double speed) {
    this->speed = speed;
    this->destinationPort = destination;

    courseVector = make_shared<Cartesian_vector>();
    courseVector->delta_x = destination.lock()->getLocation().x- getLocation().x;
    courseVector->delta_y = destination.lock()->getLocation().y- getLocation().y;
    courseDegree = to_degrees(Polar_vector(*courseVector).theta);

    status = movingToPort;
}

Status Seacraft::getStatus() const {
    return status;
}

const Point &Seacraft::getEndPosition() const {
    return *endPosition;
}

void Seacraft::setStatus(Status status) {
    Seacraft::status = status;
}

void Seacraft::stop() {
    status = stopped;
    speed = 0;
    endPosition = nullptr;
    courseVector = nullptr;
    destinationPort = weak_ptr<Port>();
}

void Seacraft::setSpeed(double speed) {
    if (!isValidSpeed(speed)){
        throw invalidSpeedException();
    }
    Seacraft::speed = speed;
}

void Seacraft::setDestinationPort(const weak_ptr<Port> &destinationPort) {
    Seacraft::destinationPort = destinationPort;
}

void Seacraft::setEndPosition(const shared_ptr<Point> &endPosition) {
    Seacraft::endPosition = endPosition;
}

void Seacraft::setCourseVector(const shared_ptr<Cartesian_vector> &courseVector) {
    Seacraft::courseVector = courseVector;
}

void Seacraft::moveOnCourse(double distance) {
    Point newLocation;
    newLocation.x = getLocation().x+distance*cos(to_radians(getCourseDegree()));
    newLocation.y = getLocation().y+distance*sin(to_radians(getCourseDegree()));
    setLocation(newLocation);
}

