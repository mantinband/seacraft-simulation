//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"

#include <utility>

Seacraft::Seacraft(string name, Point p, int strength)
: SeaObject(name,p),strength(strength){
}

string Seacraft::toString() const {
    return getName() + " (" + to_string(getPoint().x) + "," + to_string(getPoint().y) + ")" + " strength: " + to_string(strength);
}

bool Seacraft::isIn(const Point &p, double scale) const {
    bool inArea = getPoint().x > p.x-scale && getPoint().x < p.x+scale && getPoint().y > p.y-scale && getPoint().y < p.y+scale;
    bool onXRightBorder = getPoint().x == p.x+scale && getPoint().y >= p.y-scale && getPoint().y < p.y+scale;
    bool onYBottomBorder = getPoint().y == p.y-scale && getPoint().x > p.x-scale && getPoint().x <= p.x+scale;

    return inArea || onXRightBorder || onYBottomBorder;
}

string Seacraft::getInitials() const {
    return getName().substr(0,2);
}


int Seacraft::getStrength() const {
    return strength;
}
