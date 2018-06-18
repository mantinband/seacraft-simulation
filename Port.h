//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PORT_H
#define SEACRAFT_SIMULATION_PORT_H


#include <memory>
#include <queue>
#include "SeaObject.h"
#include "Seacraft.h"

/****************************************************/
/*  Class represents a port.                        */
/*  the port produces fuel and has an infinite      */
/*  amount of cargo if a cargo ship wants to load   */
/*  it supports refueling seacrafts. only one       */
/*  seacraft can refuel during an update.           */
/*  if more than one requests, it is added          */
/*  to refuel queue.                                */
/****************************************************/

class Port : public SeaObject {
public:
    Port(string name, Point point, double initialFuel, double hourlyFuelProduction);

    /*  returns string with details regarding
     *  port's status. location, fuel amount etc'    */
    string getStatusDetails() const override;

    /*  adds given seacraft to refuel queue */
    void addToRefuelQueue(const shared_ptr<Seacraft> &toAdd);

    /*  returns queue length    */
    unsigned long getRefuelQueueLength() const;

    /*  updates ports fuel amount and refuels a ship if needed  */
    void update() override;

private:
    queue<weak_ptr<Seacraft>> refuelQueue;
    double hourlyFuelProduction;
};


#endif //SEACRAFT_SIMULATION_PORT_H
