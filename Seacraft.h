//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEACRAFT_H
#define SEACRAFT_SIMULATION_SEACRAFT_H
#include <string>
#include "Geometry.h"
#include "SeaObject.h"

using namespace std;

class Seacraft : public SeaObject {
public:
    Seacraft(string name, Point p, int strength);
    bool isIn(const Point &p, double scale) const;
    string getInitials() const;

    string toString() const ; //just for debug TODO: delete before giving in

    int getStrength() const;
private:
    int strength;
};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
