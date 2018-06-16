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
    refuelQueue.push(toAdd);    //TODO: fix segmentation fault
    cout << toAdd->getName() << " added to queue" << endl;
}

/*  fuel amount += hourly fuel production
 *  refuel seacraft if queue is not empty   */
void Port::update() {

    setFuel(getFuel()+hourlyFuelProduction);
    cout << "here1" << endl;
    /*  refuel craft that is waiting to be refueled*/
    if (!refuelQueue.empty()){
        cout << refuelQueue.front()->getName() << endl;
        shared_ptr<Seacraft> toRefuel = refuelQueue.front();

        /*  if seacraft needs more fuel than is available   */
        if (Freighter::FUEL_TANK_SIZE - toRefuel->getFuel() > getFuel()){
            toRefuel->setFuel(toRefuel->getFuel()+getFuel());
            setFuel(0);
        } else {
            /*  subtract amount that is given to craft from ports total amount */
            setFuel(getFuel() - (Freighter::FUEL_TANK_SIZE - toRefuel->getFuel()));

            /*  refill craft to MAX */
            toRefuel->setFuel(Freighter::FUEL_TANK_SIZE);
        }
        refuelQueue.pop();
    }
}
