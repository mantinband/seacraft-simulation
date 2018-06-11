//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"

Seacraft::Seacraft(const string &name, double x, double y, int strength, int containers=0)
: name(name), x(x),y(y),strength(strength),containers(containers){
}

string Seacraft::toString() const {
    return name + " (" + to_string(x) + "," + to_string(y) + ")" + " strength: " + to_string(strength) + " number of containers: " + to_string(containers);
}
