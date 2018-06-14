//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_CONTROLLER_H
#define SEACRAFT_SIMULATION_CONTROLLER_H
#include "Cruiser.h"
#include "Freighter.h"
#include "PatrolBoat.h"
#include "Model.h"
#include "View.h"
#include <iostream>
using namespace std;



enum queries {
    defaultMap,
    changeMapSize,
    zoomMap,
    panMap,
    showMap,

    showStatus,
    incrementTime,
    createSeacraft,

    course,
    position,
    destination,
    load_at,
    unload_at,
    dock_at,
    attackSeacraft,
    refuelSeacraft,
    stopSeacraft,

    quit,
    invalidQuery
};




class Controller {
public:


    explicit Controller();

    void run();

    queries getQuery(string s);

    void parseLocation(Point &p);

    crafts getSeacraftType(string s);


    struct invalidLocationException : exception {
        const char* what() const throw() override {
            return "ERROR: Invalid location format. [expected: (double,double)]\n(did you forget a comma?)";
        }
    };


    struct invalidScaleException : exception {
        const char * what() const throw() override {
            return "ERROR: Invalid Scale. [expected: double]";
        }
    };

    struct invalidMapSize : exception{
        const char * what() const throw() override {
            return "ERROR: Invalid size. [expected: double]";
        }
    };
private:
    void addSeacraft();
    shared_ptr<View> view;
};


#endif //SEACRAFT_SIMULATION_CONTROLLER_H
