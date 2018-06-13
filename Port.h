//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PORT_H
#define SEACRAFT_SIMULATION_PORT_H


#include "SeaObject.h"

class Port : SeaObject {
public:
    Port(const string &name, const Point &point);
    string getStatus() const override;
};


#endif //SEACRAFT_SIMULATION_PORT_H
