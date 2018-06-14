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

    for (auto &craft : seacrafts){
        cout << craft->toString() << endl;
    }
}

string Model::getObjectInitialsAt(const Point &p, double scale) const {
    for (const auto &seacraft : seacrafts){
        if (seacraft->isIn(p, scale/2)){
            return seacraft->getInitials();
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
            if (extraInfo.empty()) {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new PatrolBoat(craftName, point, strength))); break;
            }
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
