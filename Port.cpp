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

string Port::getStatusDetails() const {
    stringstream ss;
    ss << "Port " << getName() << " at position " << getPointString()
            << ", fuel available: " << fixed << setprecision(2) << getFuel()
            << " kl" << ", hourly fuel production: "
            << fixed<< setprecision(2) << hourlyFuelProduction << " kl";
    return ss.str();
}

void Port::addToRefuelQueue(const shared_ptr<Seacraft> &toAdd) {
    refuelQueue.push(toAdd);
    cout << toAdd->getName() << " added to queue" << endl;

}
