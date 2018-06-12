//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"

#include <utility>

Seacraft::Seacraft(string name, Point p, int strength)
: name(std::move(name)), point(p),strength(strength){
}

string Seacraft::toString() const {
    return name + " (" + to_string(point.x) + "," + to_string(point.y) + ")" + " strength: " + to_string(strength);
}

bool Seacraft::isIn(const Point &p, double scale) const {
    bool inArea = point.x > p.x-scale && point.x < p.x+scale && point.y > p.y-scale && point.y < p.y+scale;
    bool onXRightBorder = point.x == p.x+scale && point.y >= p.y-scale && point.y < p.y+scale;
    bool onYBottomBorder = point.y == p.y-scale && point.x > p.x-scale && point.x <= p.x+scale;

    return inArea || onXRightBorder || onYBottomBorder;
}

string Seacraft::getInitials() const {
    return name.substr(0,2);
}
