//
// Created by amichai on 11/06/18.
//

#include <iostream> //for debugging. TODO: delete before giving in
#include "Model.h"

Model& Model::getInstance() {
    static Model instance;

    return instance;

}

Model::Model() :time(0){
}

int Model::getTime() const {
    return time;
}

void Model::addCraft(const shared_ptr<Seacraft> &toAdd) {
    seacrafts.push_back(toAdd);
}

string Model::getObjectInitialsAt(const Point &p, double scale) const {
    for (const auto &seacraft : seacrafts){
        if (seacraft->isIn(p, scale/2)){
            return seacraft->getInitials();
        }
    }
    for (const auto &port : ports){
        if (port->isIn(p, scale/2)){
            return port->getInitials();
        }
    }
    return "";
}

string Model::getStatus() const {
    string status;

    for (const auto &port : ports){
        status += port->getStatus() + "\n";
    }

    for (const auto &craft : seacrafts){
        status += craft->getStatus() + "\n";
    }

    return status;
}

void Model::addCraft(const string &craftName, const string &craftType,Point point, int strength, const string &extraInfo) {
    switch (getSeacraftType(craftType)) {
        case cruiser:
            Model::getInstance().addCraft(shared_ptr<Seacraft>(new Cruiser(craftName, point, strength)));
            break;
        case freighter:
            if (extraInfo.empty()) {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new Freighter(craftName, point, strength)));
            } else {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new Freighter(craftName, point, strength, stoi(extraInfo)))); break;
            }
            break;
        case patrol_boat:
            Model::getInstance().addCraft(shared_ptr<Seacraft>(new PatrolBoat(craftName, point, strength)));
            break;
        default:
            throw invalidCraftFormat();
    }
}
crafts Model::getSeacraftType(string s) {
    if (s == "Cruiser") return cruiser;
    if (s == "Freighter") return freighter;
    if (s == "Patrol_boat") return patrol_boat;
    return invalidCraft;
}

void Model::addPort(string portName, Point portLocation, double initialFuel, double hourlyFuelProduction) {
    try {
        ports.push_back(make_shared<Port>(portName, portLocation, initialFuel, hourlyFuelProduction));
    } catch (exception &e){
        throw e;
    }
}

void Model::setCourse(string seacraftName, double degree, double speed) {
    for (const auto &seacraft : seacrafts){
        if (seacraft->getName() == seacraftName){
            seacraft->setCourse(degree,speed);
            return;
        }
    }
    throw noSuchSeacraftException();
}

void Model::setPosition(string seacraftName, Point point, double speed) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }

    seacraft.lock()->setPosition(point, speed);
}

void Model::setDestination(const string &seacraftName,const string &portName, double speed) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }

    weak_ptr<Port> port = getPort(portName);
    if (port.lock() == weak_ptr<Port>().lock()){
        throw noSuchPortException();
    }

    seacraft.lock()->setDestination(port, speed);

}
weak_ptr<Seacraft> Model::getSeacraft(const string &seacraftName) const {
    for (const auto &seacraft : seacrafts){
        if (seacraft->getName() == seacraftName){
            return seacraft;
        }
    }
    return weak_ptr<Seacraft>();
}

weak_ptr<Port> Model::getPort(const string &portName) {
    for (const auto &port : ports){
        if (port->getName() == portName) {
            return port;
        }
    }
    return weak_ptr<Port>();
}
