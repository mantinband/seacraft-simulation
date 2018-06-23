//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"
#include "Port.h"

#include <cmath>

Seacraft::Seacraft(string name, Point p, int strength)
: SeaObject(std::move(name),p),strength(strength)
        ,status(stopped),destinationPort(weak_ptr<Port>()),courseVector(nullptr){
}

int Seacraft::getStrength() const {
    return strength;
}

void Seacraft::setCourse(double degree, double speed) {
    if (speed < 0){
        throw invalidSpeedException();
    }
    courseDegree = toRegularDegree(degree);
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

bool Seacraft::portIsInReach() {
    double distance = getDistance(getDestination().lock()->getLocation());

    /*  check if there is enough fuel.
     *  send distance to port or total distance in update,
     *  which ever is smaller   */
    if (!enoughFuelForUpdate()){
        throw notEnoughFuelForUpdateException();
    }
    return distance-getSpeed() < 0.1;
}

bool Seacraft::positionIsInReach() {
    double distance = getDistance(getEndPosition());

    /*  check if there is enough fuel.
     *  send distance to destination point or total distance in update,
     *  which ever is smaller   */
    if (!enoughFuelForUpdate()){
        throw notEnoughFuelForUpdateException();
    }

    return distance <= getSpeed();
}

bool Seacraft::enoughFuelForUpdate() {
    /*  e.x. speed: 40nm/hr. fuel consumption: 100 per nm. needed fuel: 40*100*/
    double neededFuel = getFuelConsumption()*getSpeed();

    return getFuel() >= neededFuel;
}

void Seacraft::setStrength(int strength) {
    Seacraft::strength = strength;
}

bool Seacraft::isAt(const Point &point) const {
    return getLocation().x == point.x && getLocation().y == point.y;
}

Seacraft::Seacraft(const Seacraft &rhs): SeaObject(rhs){
    strength = rhs.getStrength();
    speed = rhs.getSpeed();
    courseDegree = rhs.getCourseDegree();
    status = rhs.getStatus();
    endPosition = make_shared<Point>(rhs.getEndPosition().x,rhs.getEndPosition().y);
    destinationPort = getDestination();
    courseVector = getCourseVector();
}

const shared_ptr<Cartesian_vector> &Seacraft::getCourseVector() const {
    return courseVector;
}

Seacraft::Seacraft(Seacraft &&rhs) noexcept: SeaObject(move(rhs)){
    strength = rhs.getStrength();
    speed = rhs.getSpeed();
    courseDegree = rhs.getCourseDegree();
    status = rhs.getStatus();
    endPosition = make_shared<Point>(rhs.getEndPosition().x,rhs.getEndPosition().y);
    destinationPort = getDestination();
    courseVector = getCourseVector();

    rhs.setStrength(0);
    rhs.setSpeed(0);
    rhs.setCourseDegree(0);
    rhs.setStatus(stopped);
    rhs.setEndPosition(shared_ptr<Point>());
    rhs.setDestinationPort(weak_ptr<Port>());
    setCourseVector(shared_ptr<Cartesian_vector>());
}

void Seacraft::setCourseDegree(double courseDegree) {
    Seacraft::courseDegree = courseDegree;
}

Seacraft &Seacraft::operator=(const Seacraft &rhs){
    SeaObject::operator=(rhs);

    strength = rhs.getStrength();
    speed = rhs.getSpeed();
    courseDegree = rhs.getCourseDegree();
    status = rhs.getStatus();
    endPosition = make_shared<Point>(rhs.getEndPosition().x,rhs.getEndPosition().y);
    destinationPort = getDestination();
    courseVector = getCourseVector();
    return *this;
}

Seacraft &Seacraft::operator=(Seacraft &&rhs) noexcept{
    strength = rhs.getStrength();
    speed = rhs.getSpeed();
    courseDegree = rhs.getCourseDegree();
    status = rhs.getStatus();
    endPosition = make_shared<Point>(rhs.getEndPosition().x,rhs.getEndPosition().y);
    destinationPort = getDestination();
    courseVector = getCourseVector();

    rhs.setStrength(0);
    rhs.setSpeed(0);
    rhs.setCourseDegree(0);
    rhs.setStatus(stopped);
    rhs.setEndPosition(shared_ptr<Point>());
    rhs.setDestinationPort(weak_ptr<Port>());
    setCourseVector(shared_ptr<Cartesian_vector>());

    SeaObject::operator=(move(rhs));

    return *this;
}


