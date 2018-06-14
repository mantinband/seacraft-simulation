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
    string toString() const ; //just for debug TODO: delete before giving in
    int getStrength() const;
    void setCourse(double degree, double speed);
    void setPosition(Point point, double speed);
    struct invalidSpeedException : exception{
        const char * what() const throw() override{
            return "ERROR: Invalid speed";
        }
    };
private:
    int strength;
    double courseDegree;
    Point coursePoint;
    double speed;
};


#endif //SEACRAFT_SIMULATION_SEACRAFT_H
