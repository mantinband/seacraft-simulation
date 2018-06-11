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
