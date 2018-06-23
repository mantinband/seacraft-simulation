//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_PATROLBOAT_H
#define SEACRAFT_SIMULATION_PATROLBOAT_H


#include <set>
#include "Seacraft.h"
#include "SeacraftFactory.h"


/************************************************/
/*  Class represents a patrol boat.             */
/*  the patrol boat travels between ports.      */
/*  after reaching it's given destination,      */
/*  it calculates the closest port that hasn't  */
/*  been visited yet and travel to it.          */
/*  after visiting all ports it travels back to */
/*  its original destination port and stops     */
/*  there.                                      */
/*  every docking at port takes 3 time updates. */
/*  at the first the ship gets an option to     */
/*  refuel if port's refuel queue is empty.     */
/*  at the second it rests, and at the third    */
/*  it prepares for it's next sail.             */
/************************************************/

class PatrolBoat : public Seacraft{
public:
    static const int FUEL_TANK_SIZE = 900000;
    static const int FUEL_CONSUMPTION = 2000;
    static const int MAX_SPEED = 15;

    PatrolBoat(const string &name, Point p, int strength);
    PatrolBoat(const PatrolBoat& rhs);
    PatrolBoat& operator=(const PatrolBoat& rhs);
    PatrolBoat(PatrolBoat&& rhs) noexcept;
    PatrolBoat& operator=(PatrolBoat&& rhs) noexcept;



    virtual ~PatrolBoat() = default;
    /*  sets ship's destination port to given port at given speed   */
    void setDestination(weak_ptr<Port> destination, double speed) override;

    /*  returns ship's maximum sail speed   */
    double getMaxSpeed() const override;

    /*  returns true if given speed is valid. false otherwise   */
    bool isValidSpeed(double speed) const override;

    /*  updates ship as following:
     *
     *  #if ship is out of fuel:
     *      it stops where it's fuel finished
     *
     *  #if ship's destination port is in reach:
     *      ship's location is updated to be ports location.
     *      if the patrol boat finished visiting all ports:
     *          status is set to "stopped"
     *      if not:
     *          status is set to "docked"
     *          visit time is set to 0 (out of 3)
     *
     *  #if ship's destination is not in reach:
     *      ship continues on course
     *
     *  #if ship is docked:
     *      if current port was set a docking port:
     *          ship's status is set to "stopped"
     *      if visit time reached 3:
     *          closest port is set as next destination
     *          and ship prepares for sail
     *
     *  #if ship's status is stopped or out of fuel:
     *      do nothing  */
    void update() override;

    /*  returns ship's fuel consumption */
    double getFuelConsumption() const override;

    /*  returns class's name: "PatrolBoat"  */
    string getClassName() const override;

    /*  returns string with details regarding
     *  ship's status. location, resistance etc'    */
    string getStatusDetails() const override;

    /*  submits refuel request at current port.
     *  ONLY IF VISIT TIME == 0*/
    void refuel(weak_ptr<Seacraft> s) override;

    /*  sets ship's docking port to given port  */
    void setDockingPort(weak_ptr<Port> dockAt);

    const weak_ptr<Port> &getCurrentlyAt() const;

    const weak_ptr<Port> &getDockAt() const;

    int getNumberOfHoursAtPort() const;

    const weak_ptr<Port> &getOriginPort() const;

    const set<string> &getVisitedPorts() const;
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
    /*  set containing ports that have been visited
     *  in current cycle    */
    set<string> visitedPorts;
    /*  origin port of current cycle    */
    weak_ptr<Port> originPort;

    weak_ptr<Port> currentlyAt;
    weak_ptr<Port> dockAt;
    /*  visit time at port. (number between 0 to 3) */
    int numberOfHoursAtPort;
    /*  RegisterSeacraft object. used to register the seacraft to
     *  the seacraft factory    */
    static RegisterSeacraft registerSeacraft;
    /*  receives string containing name point strength
     *  and returns a new PatrolBoat object. used by the factory    */
    static shared_ptr<Seacraft> createPatrolBoat(const string& data);
};


#endif //SEACRAFT_SIMULATION_PATROLBOAT_H
