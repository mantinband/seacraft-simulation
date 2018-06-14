//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"

#include <utility>

Seacraft::Seacraft(string name, Point p, int strength)
: SeaObject(std::move(name),p),strength(strength){
}

string Seacraft::toString() const {
    return getName() + " (" + to_string(getPoint().x) + "," + to_string(getPoint().y) + ")" + " strength: " + to_string(strength);
}



int Seacraft::getStrength() const {
    return strength;
}

void Seacraft::setCourse(double degree, double speed) {
    if (speed < 0){
        throw invalidSpeedException();
    }
    courseDegree = degree;
    this->speed = speed;
}

void Seacraft::setPosition(Point point, double speed) {
    this->coursePoint = point;
    this->speed = speed;
    courseDegree =
}


