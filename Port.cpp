//
// Created by amichai on 11/06/18.
//

#include "Port.h"

Port::Port(const string &name, const Point &point) : SeaObject(name, point) {}

string Port::getStatus() const {
    return "Port " + getName() + " at position " + getPointString() + ", Fuel available: " + to_string(getFuel()) + " kl";
}
