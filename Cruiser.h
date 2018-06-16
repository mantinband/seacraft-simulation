//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_CRUISER_H
#define SEACRAFT_SIMULATION_CRUISER_H


#include "Seacraft.h"

class Cruiser : public Seacraft{
public:
    const static int MAX_SPEED = 75;
    const static int DEFAULT_ATTACK_RADIUS = 5;

    Cruiser(const string &craftName, Point point, int strength, float attackRadius=DEFAULT_ATTACK_RADIUS);


    string getClassName() const override;

    string getStatusDetails() const override;
private:
    float attackRadius;
};


#endif //SEACRAFT_SIMULATION_CRUISER_H
