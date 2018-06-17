//
// Created by amichai on 11/06/18.
//

#include "Port.h"
#include "Freighter.h"

Port::Port(string name, Point point, double initialFuel, double hourlyFuelProduction)
        : SeaObject(std::move(name), point) {
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
}

/*  fuel amount += hourly fuel production
 *  refuel seacraft if queue is not empty   */
void Port::update() {

    setFuel(getFuel()+hourlyFuelProduction);
    /*  check if there is a craft that is waiting to be refueled*/
    if (!refuelQueue.empty()){
        weak_ptr<Seacraft> toRefuel = refuelQueue.front();

        /*  if seacraft needs more fuel than is available   */
        if (Freighter::FUEL_TANK_SIZE - toRefuel.lock()->getFuel() > getFuel()){
            toRefuel.lock()->setFuel(toRefuel.lock()->getFuel()+getFuel());
            setFuel(0);
        } else {
            /*  subtract amount that is given to craft from ports total amount */
            setFuel(getFuel() - (Freighter::FUEL_TANK_SIZE - toRefuel.lock()->getFuel()));

            /*  refill craft to MAX */
            toRefuel.lock()->setFuel(Freighter::FUEL_TANK_SIZE);
        }
        refuelQueue.pop();
    }
}

unsigned long Port::getRefuelQueueLength() const {
    return refuelQueue.size();
}
