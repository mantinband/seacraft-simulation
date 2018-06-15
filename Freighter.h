//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_FREIGHTER_H
#define SEACRAFT_SIMULATION_FREIGHTER_H


#include "Seacraft.h"

class Freighter : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 500;
    static const int FUEL_CONSUMPTION = 1000;
    static const int MAX_SPEED = 40;

    Freighter(const string &name, Point p, int strength, int containers=0);

    string getStatusDetails() const override;

private:
    int containers;
    weak_ptr<Port> loadAt;
    weak_ptr<Port> unLoadAt;
};


#endif //SEACRAFT_SIMULATION_FREIGHTER_H
