//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PATROLBOAT_H
#define SEACRAFT_SIMULATION_PATROLBOAT_H


#include "Seacraft.h"

class PatrolBoat : Seacraft{
public:
    PatrolBoat(const string &name, double x, double y, int strength, int containers=0);

};


#endif //SEACRAFT_SIMULATION_PATROLBOAT_H
