//
// Created by amichai on 11/06/18.
//

#include "Port.h"

Port::Port(string name, Point point, double initialFuel, double hourlyFuelProduction) : SeaObject(std::move(name), point) {
    if (hourlyFuelProduction < 0){
        throw invalidFuelException();
    }

    this->hourlyFuelProduction = hourlyFuelProduction;
    setFuel(initialFuel);
}

string Port::getStatus() const {
    return "Port " + getName() + " at position " + getPointString() + ", Fuel available: " + to_string(getFuel()) + " kl";
}
