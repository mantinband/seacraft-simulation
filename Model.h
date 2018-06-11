//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_MODEL_H
#define SEACRAFT_SIMULATION_MODEL_H
#include <memory>
#include <vector>
#include "Seacraft.h"
#include "Port.h"

using namespace std;

class Model {
public:
    Model();
    static Model & getInstance();
    int getTime() const;
    void addCraft(const shared_ptr<Seacraft> &toAdd);

private:
    static shared_ptr<Model> instance;

    vector<shared_ptr<Seacraft>> seacrafts;
    vector<shared_ptr<Port>> ports;

    int time;
};


#endif //SEACRAFT_SIMULATION_MODEL_H
