//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_FREIGHTER_H
#define SEACRAFT_SIMULATION_FREIGHTER_H


#include "Seacraft.h"

class Freighter : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 500000;
    static const int FUEL_CONSUMPTION = 1000;
    static const int MAX_SPEED = 40;

    Freighter(const string &name, Point p, int strength, int containers=0);

    string getStatusDetails() const override;

    string getClassName() const override;

    void setUnloadAt(weak_ptr<Port> unloadAt, int numOfContainersToUnload);
    void setLoadAt(weak_ptr<Port> loadAt);
    void setDockingPort(weak_ptr<Port> dockAt);
    void refuel();

    bool isValidSpeed(double speed) const override;

    double getMaxSpeed() const override;

    struct invalidLoadingPortException : exception {
        const char * what() const throw() override {
            return "ERROR: Invalid loading port";
        }
    };

    struct invalidUnloadingPortException : exception {
        const char * what() const throw() override {
            return "ERROR: Invalid unloading port";
        }
    };

    struct invalidRefuelRequestException : exception {
        const char * what() const throw() override {
            return "ERROR: Invalid refuel request";
        }
    };

    struct notEnoughFuelForUpdateException : exception {
        const char * what() const throw() override {
            return "ERROR: not enough fuel for desired update";
        }
    };

    struct notEnoughContainersToUnloadException : exception {
        const char * what() const throw() override {
            return "ERROR: not enough containers to unload as desired";
        }
    };


    void update() override;
private:
    int maxContainers;
    int numContainers;

    weak_ptr<Port> loadAt;
    weak_ptr<Port> dockAt;
    weak_ptr<Port> unloadAt;

    bool portIsInReach();
    bool positionIsInReach();

    bool enoughFuelForUpdate(double distance);

    double getDistance(const Point &point);

    int numContainersToUnload;
};


#endif //SEACRAFT_SIMULATION_FREIGHTER_H
