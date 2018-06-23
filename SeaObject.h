//
// Created by amichai on 13/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEAOBJECT_H
#define SEACRAFT_SIMULATION_SEAOBJECT_H

#include <string>
#include <sstream>
#include "Geometry.h"
using namespace std;


/********************************************/
/*  Class represents an object in the sea   */
/*  the object can be a port or a ship      */
/********************************************/

class SeaObject {
public:

    SeaObject(string name, const Point &point);
    SeaObject(const SeaObject& rhs);
    SeaObject& operator=(const SeaObject& rhs);
    SeaObject(SeaObject&& rhs) noexcept;
    SeaObject& operator=(SeaObject&& rhs);
    void setName(const string &name);

    virtual ~SeaObject() = default;

    /*  returns objects name    */
    string getName() const;

    /*  returns a string representing a (x,y) point */
    string getPointString() const;

    /*  returns object's location   */
    const Point &getLocation() const;

    /*  returns fuel amount */
    double getFuel() const;

    /*  set fuel to given value */
    void setFuel(double fuel);

    /*  returns true if object is in given area */
    bool isIn(const Point &p, double scale) const;

    /*  returns objects initials    */
    string getInitials() const;

    /*  returns distance between object and given point */
    double getDistance(const Point &point);

    /*  sets objects location to given location */
    void setLocation(const Point &location);


    /***************************************************************/
    /*  pure virtual functions to be implemented by derived classes*/
    /***************************************************************/

    /*  updated objects state   */
    virtual void update()=0;

    /*  returns string with details regarding
     *  object's status. location, resistance etc'    */
    virtual string getStatusDetails() const=0;

    struct invalidFuelException : exception {
        const char *what() const throw() override{
            return "ERROR: Invalid fuel amount";
        }
    };



private:
    string name;
    Point location;
    double fuel;
};


#endif //SEACRAFT_SIMULATION_SEAOBJECT_H
