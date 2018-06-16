//
// Created by amichai on 13/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEAOBJECT_H
#define SEACRAFT_SIMULATION_SEAOBJECT_H

#include <string>
#include <sstream>
#include "Geometry.h"
using namespace std;


class SeaObject {
public:
    string getName() const;
    string getPointString() const;
    SeaObject(string name, const Point &point);
    virtual string getStatusDetails() const=0;
    const Point &getLocation() const;
    double getFuel() const;
    void setFuel(double fuel);
    bool isIn(const Point &p, double scale) const;
    string getInitials() const;

    virtual void update()=0;

    void setLocation(const Point &location);

    struct invalidFuelException : exception {
        const char *what() const throw() override{
            return "Fuel amount must be positive";
        }
    };

private:
    string name;
    Point location;
    double fuel;
};


#endif //SEACRAFT_SIMULATION_SEAOBJECT_H
