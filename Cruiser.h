//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_CRUISER_H
#define SEACRAFT_SIMULATION_CRUISER_H


#include "Seacraft.h"

class Cruiser : Seacraft{
public:
    Cruiser(const string &name, Point p, int strength, int containers=0);

};


#endif //SEACRAFT_SIMULATION_CRUISER_H
