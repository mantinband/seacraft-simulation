//
// Created by amichai on 11/06/18.
//

#include "Seacraft.h"
#include "Port.h"

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
    courseVector = nullptr;
}

void Seacraft::setPosition(Point point, double speed) {
    this->speed = speed;
    courseVector = make_shared<Cartesian_vector>();
    courseVector->delta_x = point.x-getPoint().x;
    courseVector->delta_y = point.y-getPoint().y;

    courseDegree = to_degrees(Polar_vector(*courseVector).theta);
}

double Seacraft::getCourseDegree() const {
    return courseDegree;
}

double Seacraft::getSpeed() const {
    return speed;
}

weak_ptr<Port> Seacraft::getDestination() const {
    return destination;
}

const shared_ptr<Cartesian_vector> &Seacraft::getCourseVector() const {
    return courseVector;
}


void Seacraft::setDestination(weak_ptr<Port> destination, double speed) {
    this->speed = speed;
    this->destination = destination;
    courseVector = make_shared<Cartesian_vector>();
    courseVector->delta_x = destination.lock()->getPoint().x-getPoint().x;
    courseVector->delta_y = destination.lock()->getPoint().y-getPoint().y;
    cout << courseVector->delta_x << " " << courseVector->delta_y << endl;
    courseDegree = to_degrees(Polar_vector(*courseVector).theta);

}


