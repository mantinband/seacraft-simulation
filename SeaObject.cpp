//
// Created by amichai on 13/06/18.
//

#include "SeaObject.h"

SeaObject::SeaObject(string name, const Point &point) : name(move(name)), point(point) {}

const Point &SeaObject::getPoint() const {
    return point;
}

string SeaObject::getName() const {
    return name;
}

string SeaObject::getPointString() const {
    stringstream ss;
    ss << "(" << fixed << setprecision(2) << point.x << ", " << fixed << setprecision(2) << point.y << ")";
    return ss.str();
}

double SeaObject::getFuel() const {
    return fuel;
}

void SeaObject::setFuel(double fuel) {
    if (fuel < 0){
        throw invalidFuelException();
    }
    SeaObject::fuel = fuel;
}

bool SeaObject::isIn(const Point &p, double scale) const {
    bool inArea = getPoint().x > p.x-scale && getPoint().x < p.x+scale && getPoint().y > p.y-scale && getPoint().y < p.y+scale;
    bool onXRightBorder = getPoint().x == p.x+scale && getPoint().y >= p.y-scale && getPoint().y < p.y+scale;
    bool onYBottomBorder = getPoint().y == p.y-scale && getPoint().x > p.x-scale && getPoint().x <= p.x+scale;

    return inArea || onXRightBorder || onYBottomBorder;
}

string SeaObject::getInitials() const {
    return getName().substr(0,2);
}