//
// Created by amichai on 13/06/18.
//

#include "SeaObject.h"

SeaObject::SeaObject(string name, const Point &point) : name(move(name)), point(point) {}

const Point &SeaObject::getPoint() const {
    return point;
}

string SeaObject::getName() const {
    return name;
}

string SeaObject::getPointString() const {
    stringstream ss;
    ss << "(" << fixed << setprecision(2) << point.x << ", " << fixed << setprecision(2) << point.y << ")";
    return ss.str();
}

double SeaObject::getFuel() const {
    return fuel;
}

void SeaObject::setFuel(double fuel) {
    SeaObject::fuel = fuel;
}
