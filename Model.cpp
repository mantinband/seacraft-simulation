//
// Created by amichai on 11/06/18.
//

#include <iostream> //for debugging. TODO: delete before giving in
#include <limits>
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
        status += port->getStatusDetails() + "\n";
    }

    for (const auto &craft : seacrafts){
        status += craft->getStatusDetails() + "\n";
    }

    return status;
}

void Model::addCraft(const string &craftName, const string &craftType,Point point, int strength, const string &extraInfo) {
    switch (getSeacraftType(craftType)) {
        case cruiser:
            if (extraInfo.empty()) {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new Cruiser(craftName, point, strength)));
            } else {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new Cruiser(craftName, point, strength, stof(extraInfo))));
            }
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
    ports.push_back(make_shared<Port>(portName, portLocation, initialFuel, hourlyFuelProduction));
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
weak_ptr<Seacraft> Model::getSeacraft(const string &theName) const {
    for (const auto &seacraft : seacrafts){
        if (seacraft->getName() == theName){
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

bool Model::seacraftExists(const string &seacraftName) const {
    return getSeacraft(seacraftName).lock() != weak_ptr<Seacraft>().lock();
}

void Model::addLoadDestination(const string &seacraftName, const string &portDestination) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }
    weak_ptr<Port> port = getPort(portDestination);

    if (port.lock() == weak_ptr<Port>().lock()){
        throw noSuchPortException();
    }

    if (seacraft.lock()->getClassName() != "Freighter"){
        throw invalidCraftException();
    }

    Freighter &f = *dynamic_cast<Freighter*>(&*(seacraft.lock()));
    f.setLoadAt(port);
}

void Model::addUnloadDestination(string seacraftName, string portDestination, int numOfContainersToUnload) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }
    weak_ptr<Port> port = getPort(portDestination);

    if (port.lock() == weak_ptr<Port>().lock()){
        throw noSuchPortException();
    }

    if (seacraft.lock()->getClassName() != "Freighter"){
        throw invalidCraftException();
    }

    Freighter &f = *dynamic_cast<Freighter*>(&*(seacraft.lock()));
    f.setUnloadAt(port, numOfContainersToUnload);
}

void Model::setDockingPort(const string &seacraftName, const string &portDestination) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }
    weak_ptr<Port> port = getPort(portDestination);

    if (port.lock() == weak_ptr<Port>().lock()){
        throw noSuchPortException();
    }

    if (seacraft.lock()->getClassName() != "Freighter"){
        throw invalidCraftException();
    }

    Freighter &f = *dynamic_cast<Freighter*>(&*(seacraft.lock()));
    f.setDockingPort(port);
}

void Model::refuelCraft(const string &seacraftName) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }

    if (seacraft.lock()->getClassName() == "Cruiser"){
        throw invalidCraftException();
    }

    dynamic_cast<Freighter *>(&*seacraft.lock())->refuel(seacraft);
}

void Model::stopSeacraft(const string &seacraftName) {
    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);

    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }

    seacraft.lock()->stop();
}

void Model::attackSeacraft(const string &pirateShipName,const string &seacraftName) {
    weak_ptr<Seacraft> pirateCraft = getSeacraft(pirateShipName);

    if (pirateCraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }


    weak_ptr<Seacraft> seacraft = getSeacraft(seacraftName);


    if (seacraft.lock() == weak_ptr<Seacraft>().lock()){
        throw noSuchSeacraftException();
    }

    if (pirateCraft.lock()->getClassName() != "Cruiser" || seacraft.lock()->getClassName() == "Cruiser"){
        throw invalidCraftException();
    }

    dynamic_cast<Cruiser*>(&*pirateCraft.lock())->attack(seacraft);
}

void Model::update() {
    time++;

    for (const auto &port : ports){
        port->update();
    }
    for (const auto &seacraft : seacrafts){
        seacraft->update();
    }
}

weak_ptr<Port> Model::getClosestPort(const Point &point, set<string> visitedPorts) const {
    double shortestDistance = numeric_limits<double>::max();
    weak_ptr<Port> closestPort = weak_ptr<Port>();

    for (const auto &port : ports){
        if (visitedPorts.find(port->getName()) == visitedPorts.end()){
            if (port->getDistance(point) < shortestDistance){
                shortestDistance = port->getDistance(point);
                closestPort = port;
            }
        }
    }
    return closestPort;
}
