//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PATROLBOAT_H
#define SEACRAFT_SIMULATION_PATROLBOAT_H


#include "Seacraft.h"

class PatrolBoat : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 900000;

    double getMaxSpeed() const override;

    static const int FUEL_CONSUMPTION = 2000;
    static const int MAX_SPEED = 15;

    bool isValidSpeed(double speed) const override;

    void update() override;

    string getClassName() const override;

    PatrolBoat(const string &name, Point p, int strength);

    string getStatusDetails() const override;
};


#endif //SEACRAFT_SIMULATION_PATROLBOAT_H
