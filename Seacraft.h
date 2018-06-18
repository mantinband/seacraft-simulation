//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEACRAFT_H
#define SEACRAFT_SIMULATION_SEACRAFT_H
#include <string>
#include <memory>
#include "Geometry.h"
#include "SeaObject.h"
using namespace std;
class Port;

/*  seacraft possible states    */
enum Status{
    movingToPosition,
    movingToPort,
    movingOnCourse,
    dockedAt,
    stopped,
    deadInTheWater
};

/****************************************/
/*  abstract class representing a ship. */
/****************************************/

class Seacraft : public SeaObject {
public:
    Seacraft(string name, Point p, int strength);


    /*  sets ships location to given distance from current spot.
     *  new location is based on ships sailing angle    */
    void moveOnCourse(double distance);

    /*  returns ships strength. attack force for pirate ship, resistance for others */
    int getStrength() const;

    /*  returns enum value representing ships status*/
    Status getStatus() const;

    /*  returns ship's sailing speed    */
    double getSpeed() const;

    /*  returns weak pointer to ship's destination port */
    weak_ptr<Port> getDestination() const;

    /*  returns ships sailing angle */
    double getCourseDegree() const;

    /*  returns final destination end point */
    const Point &getEndPosition() const;

    /*  stops ship  */
    void stop();

    /*  sets ships sailing to given angle at given speed    */
    virtual void setCourse(double degree, double speed);

    /*  sets ships destination to given point at given speed    */
    virtual void setPosition(Point point, double speed);

    /*  sets ships destination to given port at given speed */
    virtual void setDestination(weak_ptr<Port> destination, double speed);

    /*  sets ships status to given status   */
    void setStatus(Status status);

    /*  sets ships speed to given speed */
    void setSpeed(double speed);

    /*  sets ships end (x,y) point to given point   */
    void setEndPosition(const shared_ptr<Point> &endPosition);

    /*  sets ships destination port to given port   */
    void setDestinationPort(const weak_ptr<Port> &destinationPort);

    /*  sets course vector to given vector  */
    void setCourseVector(const shared_ptr<Cartesian_vector> &courseVector);


    /*  returns true if ship is at given point  */
    bool isAt(const Point &point) const;

    /*  sets ship resistance/attack strength to given value */
    void setStrength(int strength);


    /*  returns true if end point is reachable during next update, false otherwise   */
    bool positionIsInReach();

    /*  returns true if port is reachable during next update, false otherwise   */
    bool portIsInReach();

    /*  returns true if ship has enough fuel to finish next update. false otherwise */
    bool enoughFuelForUpdate();


    /****************************************************************/
    /*  pure virtual functions to be implemented by derived classes */
    /****************************************************************/

    /*  returns class's name    */
    virtual string getClassName() const =0;

    /*  returns true if given speed is valid, false otherwise    */
    virtual bool isValidSpeed(double speed) const =0;

    /*  returns ship's maximum sail speed   */
    virtual double getMaxSpeed() const=0;

    /*  returns ship's fuel consumption */
    virtual double getFuelConsumption() const=0;

    /*  submits refuel request at current port  */
    virtual void refuel(weak_ptr<Seacraft>) =0;

    struct invalidSpeedException : exception{
        const char * what() const throw() override{
            return "ERROR: Invalid speed";
        }
    };

    struct unexpectedStateException : exception{
        const char * what() const throw() override {
            return "ERROR: Unexpected state";
        }
    };


    struct notEnoughFuelForUpdateException : exception {
        const char * what() const throw() override {
            return "ERROR: not enough fuel for desired update";
        }
    };



private:
    /*  ship's attack/resistance strength   */
    int strength;

    /*  ship's sailing speed    */
    double speed;

    /*  ship's sailing angle    */
    double courseDegree;

    Status status;
    shared_ptr<Point> endPosition;
    weak_ptr<Port> destinationPort;
    shared_ptr<Cartesian_vector> courseVector;
};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
