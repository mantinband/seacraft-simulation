//
// Created by amichai on 13/06/18.
//

#include <cmath>
#include "SeaObject.h"

SeaObject::SeaObject(string name, const Point &point) : name(move(name)), location(point) {}

const Point &SeaObject::getLocation() const {
    return location;
}

string SeaObject::getName() const {
    return name;
}

string SeaObject::getPointString() const {
    stringstream ss;
    ss << "(" << fixed << setprecision(2) << location.x << ", " << fixed << setprecision(2) << location.y << ")";
    return ss.str();
}

double SeaObject::getFuel() const {
    return fuel;
}

void SeaObject::setFuel(double fuel) {
    if (fuel < 0){
        throw invalidFuelException();
    }
    SeaObject::fuel = fuel;
}

bool SeaObject::isIn(const Point &p, double scale) const {
    bool inArea = getLocation().x > p.x-scale && getLocation().x < p.x+scale && getLocation().y > p.y-scale &&
            getLocation().y < p.y+scale;
    bool onXRightBorder = getLocation().x == p.x+scale && getLocation().y >= p.y-scale && getLocation().y < p.y+scale;
    bool onYBottomBorder = getLocation().y == p.y-scale && getLocation().x > p.x-scale && getLocation().x <= p.x+scale;

    return inArea || onXRightBorder || onYBottomBorder;
}

string SeaObject::getInitials() const {
    return getName().substr(0,2);
}

void SeaObject::setLocation(const Point &location) {
    SeaObject::location = location;
}


double SeaObject::getDistance(const Point &point) {
    double distance = square(getLocation().x-point.x) + square(getLocation().y-point.y);
    distance = sqrt(distance);
    return distance;
}

SeaObject::SeaObject(const SeaObject &rhs) {
    name = rhs.getName();
    location = rhs.getLocation();
    fuel = rhs.getFuel();
}

SeaObject &SeaObject::operator=(const SeaObject &rhs) {
    name = rhs.getName();
    location = rhs.getLocation();
    fuel = rhs.getFuel();
    return *this;
}

SeaObject::SeaObject(SeaObject &&rhs) noexcept{
    name = rhs.getName();
    location = rhs.getLocation();
    fuel = rhs.getFuel();
    rhs.setName("");
    rhs.setLocation(Point());
    rhs.setFuel(0);
}

void SeaObject::setName(const string &name) {
    SeaObject::name = name;
}

SeaObject &SeaObject::operator=(SeaObject &&rhs) noexcept {
    name = rhs.getName();
    location = rhs.getLocation();
    fuel = rhs.getFuel();
    rhs.setName("");
    rhs.setLocation(Point());
    rhs.setFuel(0);

    return *this;
}

