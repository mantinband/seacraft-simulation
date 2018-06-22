//
// Created by amichai on 21/06/18.
//

#ifndef SEACRAFT_SIMULATION_SEACRAFTFACTORY_H
#define SEACRAFT_SIMULATION_SEACRAFTFACTORY_H

#include <map>
#include "Seacraft.h"
/****************************************************/
/*  class receives seacraft information and creates */
/*  a new seacraft accordingly                      */
/*  each seacraft registers itself to factory during*/
/*  initialization of it's class                    */
/*  when registering it provides a function to be   */
/*  called upon for creating a seacraft of it's type*/
/*  it's design pattern is a singleton and is       */
/*  publicly accessible.                            */
/****************************************************/

class SeacraftFactory {
public:
    /*  returns instance of the factory */
    static SeacraftFactory& getInstance();

    /*  receives seacraft information and returns a new seacraft object accordingly */
    shared_ptr<Seacraft>
    create(const string &craftName, const string &craftType, Point point, int strength, const string &extraInfo);


    struct invalidCraftFormat: exception {
        const char * what() const throw() override {
            return "ERROR: Invalid seacraft format. [expected: <name> <type> <coordinates> <strength> (optional: number of maxContainers)";
        }
    };

    /*  registers seacraft to factory. added as a pair of "seacraft type name"
     *  and a function used to create an instance of the seacraft   */
    void registerSeacraft(const string &seacraftType,
                          shared_ptr<Seacraft> (*creationFunction)(const string &));

    /*  if seacraft is'nt registered    */
    struct unknownSeacraftTypeException : exception {
        const char * what() const throw() override {
            return "ERROR: unknown seacraft type.";
        }
    };
protected:
    /*  map holding seacraft types and functions to create each one */
    map<string,shared_ptr<Seacraft>(*)(const string&)> registry;
    SeacraftFactory()= default;

};

/*  used by seacrafts in order to register themselves to registry
 *  each seacraft holds a static "RegisterSeacraft" object which when
 *  initialized calls constructor with it's name and creation function
 *  (see Cruiser Freighter or Controller .cpp files for examples)   */
struct RegisterSeacraft : SeacraftFactory {
    RegisterSeacraft(const string &seacraftType,
                                           shared_ptr<Seacraft> (*creationFunction)(const string &)) {
        SeacraftFactory::getInstance().registerSeacraft(seacraftType,creationFunction);
    }
};


#endif //SEACRAFT_SIMULATION_SEACRAFTFACTORY_H
