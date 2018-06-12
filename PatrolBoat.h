//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PATROLBOAT_H
#define SEACRAFT_SIMULATION_PATROLBOAT_H


#include "Seacraft.h"

class PatrolBoat : public Seacraft{
public:
    PatrolBoat(const string &name, Point p, int strength);
};


#endif //SEACRAFT_SIMULATION_PATROLBOAT_H
