//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEACRAFT_H
#define SEACRAFT_SIMULATION_SEACRAFT_H
#include <string>
#include "Geometry.h"

using namespace std;

class Seacraft {

public:
    Seacraft(string name, Point p, int strength, int containers=0);
    bool isIn(const Point &p, double scale) const;
    string getInitials() const;

    string toString() const ; //just for debug TODO: delete before giving in
private:
    string name;
    Point point;
    int strength;
    int containers;
};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
