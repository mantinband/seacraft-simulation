//
// Created by amichai on 11/06/18.
//

#include <iostream> //for debugging. TODO: delete before giving in
#include "Model.h"

Model& Model::getInstance() {
    if (instance == nullptr){
        instance = make_shared(new Model);
    }
    return *instance;

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
