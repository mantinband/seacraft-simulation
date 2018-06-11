//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEACRAFT_H
#define SEACRAFT_SIMULATION_SEACRAFT_H
#include <string>
using namespace std;

class Seacraft {

public:
    Seacraft(const string &name, double x, double y, int strength, int containers);

    string toString() const ; //just for debug TODO: delete before giving in
private:
    string name;
    double x,y;
    int strength;
    int containers;
};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
