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
#include <fstream>
#include <iostream>
using namespace std;


/*  query options   */
enum queries {
    defaultMap,
    changeMapSize,
    zoomMap,
    panMap,
    showMap,
    showStatus,
    go,
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

/*****************************************************/
/*  class interacts with user. receives queries and  */
/* commutes with the view and model classes          */
/*****************************************************/

class Controller {
public:

    explicit Controller();
    virtual ~Controller()= default;
    Controller& operator=(const Controller& rhs);
    Controller(Controller &&rhs) noexcept;
    Controller& operator=(Controller&& rhs) noexcept ;

    /*  receives and executes queries*/
    void run(ifstream &inputFile);

    /*  returns enum value according to given string token  */
    queries getQuery(string s);

    /*  reads point location from given stream into given point */
    void parseLocation(Point &p, istream &is);

    void setView(const shared_ptr<View> &view);

    const shared_ptr<View> &getView() const;

    struct invalidLocationException : exception {
        const char* what() const throw() override {
            return "ERROR: Invalid location format. [expected: (double,double)]\n(did you forget a comma?)";
        }
    };


    struct invalidPortFileException : exception {
        const char *what() const throw() override {
            return "ERROR: Invalid port file."
                    "\nexpected: file with lines that follow:"
                    "\n[ portName (locationX,locationY) hourlyFuelProduction hourlyFuelProduction ]";
        }
    };


    struct invalidCraftNameException : exception {
        const char * what() const throw() override{
            return "ERROR: Invalid craft name";
        }
    };

private:

    /*  strong pointer to the view  */
    shared_ptr<View> view;
    /*  default port to be created in any event */
    static const string INITIAL_PORT;

    /*  receives craft data from standard input and sends it to the model   */
    void addSeacraft();

    /*  reads port data from given file and sends it to the model */
    void createPorts(ifstream &inputFile);

    /*  query options that follow a seacraft name   */
    void seacraftOptions(string seacraftName);
};



#endif //SEACRAFT_SIMULATION_CONTROLLER_H
