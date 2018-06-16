//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PORT_H
#define SEACRAFT_SIMULATION_PORT_H


#include <memory>
#include <queue>
#include "SeaObject.h"
#include "Seacraft.h"

class Port : public SeaObject {
public:
    Port(string name, Point point, double initialFuel, double hourlyFuelProduction);
    string getStatusDetails() const override;
    void addToRefuelQueue(const shared_ptr<Seacraft> &toAdd);

    void update() override;

private:
    queue<shared_ptr<Seacraft>> refuelQueue;
    double hourlyFuelProduction;
};


#endif //SEACRAFT_SIMULATION_PORT_H
