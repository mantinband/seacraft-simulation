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
    return "(" + to_string(point.x) +"," + to_string(point.y) + ")";
}

double SeaObject::getFuel() const {
    return fuel;
}

void SeaObject::setFuel(double fuel) {
    SeaObject::fuel = fuel;
}
