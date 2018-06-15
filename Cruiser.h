//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_CRUISER_H
#define SEACRAFT_SIMULATION_CRUISER_H


#include "Seacraft.h"

class Cruiser : public Seacraft{
public:
    Cruiser(const string &name, Point p, int strength);
    Cruiser(const string &craftName, Point point, int strength, float attackRadius);
    string getStatus() const override;
private:
    float attackRadius;
};


#endif //SEACRAFT_SIMULATION_CRUISER_H
