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


enum Status{
    movingToPosition,
    movingToPort,
    movingOnCourse,
    dockedAt,
    stopped,
    deadInTheWater
};

class Seacraft : public SeaObject {
public:
    Seacraft(string name, Point p, int strength);


    void moveOnCourse(double distance);
    int getStrength() const;
    Status getStatus() const;
    double getSpeed() const;
    weak_ptr<Port> getDestination() const;

    double getCourseDegree() const;
    const Point &getEndPosition() const;

    void stop();
    virtual void setCourse(double degree, double speed);
    virtual void setPosition(Point point, double speed);
    virtual void setDestination(weak_ptr<Port> destination, double speed);

    void setStatus(Status status);
    void setSpeed(double speed);
    void setEndPosition(const shared_ptr<Point> &endPosition);
    void setDestinationPort(const weak_ptr<Port> &destinationPort);
    void setCourseVector(const shared_ptr<Cartesian_vector> &courseVector);

    virtual string getClassName() const =0;
    virtual bool isValidSpeed(double speed) const =0;
    virtual double getMaxSpeed() const=0;
    virtual double getFuelConsumption() const=0;
    virtual void refuel(weak_ptr<Seacraft>) =0;

    void setStrength(int strength);

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



    bool portIsInReach();
    bool positionIsInReach();
    bool enoughFuelForUpdate();
private:
    int strength;
    double speed;
    double courseDegree;
    Status status;
    shared_ptr<Point> endPosition;
    weak_ptr<Port> destinationPort;

    shared_ptr<Cartesian_vector> courseVector;
};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
