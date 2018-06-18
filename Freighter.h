//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_FREIGHTER_H
#define SEACRAFT_SIMULATION_FREIGHTER_H


#include "Seacraft.h"

/****************************************************/
/*  Class represents a cargo ship.                  */
/*  a cargo ship can sail from port to port,        */
/*  set a point in the sea or an angle.             */
/*  it has a "strength" that represents             */
/*  it's resistance from an attack by a             */
/*  pirate ship.                                    */
/*  optional: it can load and unload cargo at ports.*/
/****************************************************/

class Freighter : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 500000;
    static const int FUEL_CONSUMPTION = 1000;
    static const int MAX_SPEED = 40;

    Freighter(const string &name, Point p, int strength, int containers=0);

    /*  returns string with details regarding
     *  ship's status. location, resistance etc'    */
    string getStatusDetails() const override;

    /*  returns class name: "Freighter"  */
    string getClassName() const override;

    /*  sets a port to unload a given number of containers  */
    void setUnloadAt(weak_ptr<Port> unloadAt, int numOfContainersToUnload);

    /*  sets a port to load ship to it's max container capacity */
    void setLoadAt(weak_ptr<Port> loadAt);

    /*  sets a port for docking */
    void setDockingPort(weak_ptr<Port> dockAt);

    /*  put refuel request. if line to refuel is not empty
     *  ship is added to refuel queue. (FIFO)   */
    void refuel(weak_ptr<Seacraft> ptr) override;

    /*  returns true if given speed is valid, false othrewise   */
    bool isValidSpeed(double speed) const override;

    /*  returns ships maximum sail speed    */
    double getMaxSpeed() const override;

    /*  returns ship's fuel consumption */
    double getFuelConsumption() const override;

    /*  updates ship as following:
     *
     *  #if ship is does not have enough fuel to finish
     *      current update it stops where the fuel ran out.
     *
     *  #if ship is headed to port:
     *      if destination port is in reach:
     *          it's location is set to the port's location,
     *          and it's status is updated to "docked"
     *      if not:
     *          ship's location is set according to course.
     *
     *  #if ship is headed to given point:
     *      if point is in reach:
     *          it's location is set to the point's location,
     *          and it's status is updated to stopped.
     *      if not:
     *          ship's location is set according to course.
     *
     *  #if ship is stopped or out of fuel:
     *      no update takes place.
     *  */
    void update() override;

    /*  sets ship's direction to given angle, at given speed.
     *  updates "currently at" field to "none"  */
    void setCourse(double degree, double speed) override;

    /*  sets ship's destination to given point, at given speed.
     *  updates "currently at" field to "none" */
    void setPosition(Point point, double speed) override;

    /*  sets ship's destination to given port, at given speed.
     *  updates "currently at" field to "none" */
    void setDestination(weak_ptr<Port> destination, double speed) override;

    /*  sets ship's number of containers to given number    */
    void setNumContainers(int numContainers);

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

    struct notEnoughContainersToUnloadException : exception {
        const char * what() const throw() override {
            return "ERROR: not enough containers to unload as desired";
        }
    };

private:
    int maxContainers;
    int numContainers;

    weak_ptr<Port> loadAt;
    weak_ptr<Port> dockAt;
    weak_ptr<Port> unloadAt;
    weak_ptr<Port> currentlyAt;

    int numContainersToUnload;
};


#endif //SEACRAFT_SIMULATION_FREIGHTER_H
