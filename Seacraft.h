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
    string toString() const ; //just for debug TODO: delete before giving in
    int getStrength() const;
    void setCourse(double degree, double speed);
    void setPosition(Point point, double speed);

    Status getStatus() const;

    double getSpeed() const;

    weak_ptr<Port> getDestination() const;

    const shared_ptr<Cartesian_vector> &getCourseVector() const;

    double getCourseDegree() const;

    virtual string getClassName() const =0;

    void setDestination(weak_ptr<Port> destination, double speed);

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
private:
    int strength;
    double speed;
    double courseDegree;
    Status status;
    Point endPosition;
    weak_ptr<Port> destination;
    shared_ptr<Cartesian_vector> courseVector;
public:
    const Point &getEndPosition() const;

};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
