//
// Created by amichai on 13/06/18.
//

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
