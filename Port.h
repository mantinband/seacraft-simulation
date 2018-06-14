//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PORT_H
#define SEACRAFT_SIMULATION_PORT_H


#include "SeaObject.h"

class Port : public SeaObject {
public:
    Port(string name, Point point, double initialFuel, double hourlyFuelProduction);
    string getStatus() const override;


private:
    double hourlyFuelProduction;
};


#endif //SEACRAFT_SIMULATION_PORT_H
