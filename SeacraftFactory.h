//
// Created by amichai on 21/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEACRAFTFACTORY_H
#define SEACRAFT_SIMULATION_SEACRAFTFACTORY_H

#include <map>
#include "Seacraft.h"


class SeacraftFactory {
public:
    static SeacraftFactory& getInstance();
    shared_ptr<Seacraft>
    create(const string &basicString, const string &string1, Point point, int i, const string &string2);
    struct invalidCraftFormat: exception {
        const char * what() const throw() override {
            return "ERROR: Invalid seacraft format. [expected: <name> <type> <coordinates> <strength> (optional: number of maxContainers)";
        }
    };

    struct unknownSeacraftTypeException : exception {
        const char * what() const throw() override {
            return "ERROR: unknown seacraft type.";
        }
    };

    void registerSeacraft(const string &seacraftType,
                          shared_ptr<Seacraft> (*creationFunction)(const string &));
protected:
    map<string,shared_ptr<Seacraft>(*)(const string&)> registry;
};

struct RegisterSeacraft : SeacraftFactory {
    RegisterSeacraft(const string &seacraftType,
                                           shared_ptr<Seacraft> (*creationFunction)(const string &)) {
        SeacraftFactory::getInstance().registerSeacraft(seacraftType,creationFunction);
    }
};


#endif //SEACRAFT_SIMULATION_SEACRAFTFACTORY_H
