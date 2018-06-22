//
// Created by amichai on 21/06/18.
//

#include "SeacraftFactory.h"

shared_ptr<Seacraft> SeacraftFactory::create(const string &craftName, const string &craftType, Point point, int strength, const string &extraInfo) {
    shared_ptr<Seacraft> newCraft;
    stringstream ss;

    /*  create string holding craft information */
    if (craftName.empty() || strength < 0){
        throw invalidCraftFormat();
    }

    ss << craftName << " " << point.x << " " << point.y << " " << strength << " ";

    if (!extraInfo.empty()){
        ss << extraInfo << " ";
    }


    if (registry.find(craftType) == registry.end()){
        throw unknownSeacraftTypeException();
    }
    /*  call "craftType"'s creation function    */
    return registry[craftType](ss.str());
}

SeacraftFactory &SeacraftFactory::getInstance() {
    static SeacraftFactory instance;

    return instance;
}

void SeacraftFactory::registerSeacraft(const string &seacraftType,
                                       shared_ptr<Seacraft> (*creationFunction)(const string &)) {
    registry[seacraftType] = creationFunction;
}


