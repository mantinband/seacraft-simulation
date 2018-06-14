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


