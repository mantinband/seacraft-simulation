//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_FREIGHTER_H
#define SEACRAFT_SIMULATION_FREIGHTER_H


#include "Seacraft.h"

class Freighter : public Seacraft{
public:
    Freighter(const string &name, Point p, int strength, int containers=0);
private:
    int containers;
};


#endif //SEACRAFT_SIMULATION_FREIGHTER_H
