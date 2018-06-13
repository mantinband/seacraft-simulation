//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PATROLBOAT_H
#define SEACRAFT_SIMULATION_PATROLBOAT_H


#include "Seacraft.h"

class PatrolBoat : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 900;
    PatrolBoat(const string &name, Point p, int strength);

    string getStatus() const override;
};


#endif //SEACRAFT_SIMULATION_PATROLBOAT_H
