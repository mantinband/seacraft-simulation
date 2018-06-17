//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PATROLBOAT_H
#define SEACRAFT_SIMULATION_PATROLBOAT_H


#include <set>
#include "Seacraft.h"

class PatrolBoat : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 900000;
    static const int FUEL_CONSUMPTION = 2000;
    static const int MAX_SPEED = 15;

    PatrolBoat(const string &name, Point p, int strength);

    void setDestination(weak_ptr<Port> destination, double speed) override;

    double getMaxSpeed() const override;
    bool isValidSpeed(double speed) const override;
    void update() override;

    double getFuelConsumption() const override;

    string getClassName() const override;
    string getStatusDetails() const override;

    void refuel(weak_ptr<Seacraft> s) override;

    struct invalidRefuelRequestException : exception{
        const char * what() const throw() override{
            return "ERROR: Invalid refuel request. (refuel request should be"
                    "done in the first docking hour ";
        }
    };
    struct refuelQueueNotEmptyException : exception{
        const char * what() const throw() override{
            return "ERROR: refuel queue not empty";
        }
    };
private:
    set<string> visitedPorts;
    weak_ptr<Port> originPort;
    weak_ptr<Port> currentlyAt;
    int numberOfHoursAtPort;
};


#endif //SEACRAFT_SIMULATION_PATROLBOAT_H
