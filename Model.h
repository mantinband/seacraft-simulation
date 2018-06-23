//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_MODEL_H
#define SEACRAFT_SIMULATION_MODEL_H
#include <memory>
#include <vector>
#include "Seacraft.h"
#include "Port.h"
#include "Freighter.h"
#include "Cruiser.h"
#include "PatrolBoat.h"

using namespace std;

/********************************************/
/*  Class is the simulation's database.     */
/*  it holds all sea objects and supports   */
/*  queries and data manipulation.          */
/*  it's design pattern is a singleton      */
/*  and is publicly accessible              */
/********************************************/

class Model {
public:
    /*  returns instance of model   */
    static Model & getInstance();

    /*  returns current time    */
    int getTime() const;

    /*  returns initials of object in given area if found. empty string otherwise   */
    string getObjectInitialsAt(const Point &p, double scale) const;

    /*  returns string with all sea objects statuses    */
    string getStatus() const;

    /*  adds port to ports vector*/
    void addPort(string portName, Point portLocation, double initialFuel, double hourlyFuelProduction);

    /*  receives as arguments ship information. and uses seacraft
     *  factory to generate the correct seacraft    */
    void addCraft(const string &craftName, const string &crafType, Point point, int strength, const string &extraInfo);

    /*  sets given seacraft's destination to given angle at given speed    */
    void setCourse(string seacraftName, double degree, double speed);

    /*  set given seacraft's destination to given point at given speed  */
    void setPosition(string seacraftName, Point point, double speed);

    /*  sets given seacraft's destination to given port at given speed  */
    void setDestination(const string &seacraftName,const string &portName, double speed);

    /*  returns true if given seacraft exists, false otherwise  */
    bool seacraftExists(const string &seacraftName) const;

    /*  adds given port as loading port for given seacraft  */
    void addLoadDestination(const string &seacraftName,const string &portDestination);

    /*  adds given port as unloading port for given seacraft and sets number of containers to unload   */
    void addUnloadDestination(string seacraftName, string portDestination, int numOfContainersToUnload);

    /*  sets docking port for given seacraft    */
    void setDockingPort(const string &seacraftName,const string &portDestination);

    /*  adds refuel request for given seacraft  */
    void refuelCraft(const string &seacraftName);

    /*  stops seacrafts sail    */
    void stopSeacraft(const string &seacraftName);

    /*  adds attack request to given pirate ship to given seacraft  */
    void attackSeacraft(const string &pirateShipName, const string &seacraftName);

    /*  updates all seaobject   */
    void update();

    /*  returns closest port to given point that isn't in visitedPorts set  */
    weak_ptr<Port> getClosestPort(const Point &point, set<string> visitedPorts) const ;

    struct unexpectedStateException : exception{
        const char * what() const throw() override {
            return "ERROR: Unexpected state";
        }
    };


    struct noSuchSeacraftException : exception {
        const char *what() const throw() override{
            return "ERROR: No such seacraft";
        }
    };

    struct noSuchPortException : exception {
        const char * what() const throw() override {
            return "ERROR: No such port";
        }
    };

    struct invalidCraftException : exception {
        const char * what() const throw() override{
            return "ERROR: Invalid craft";
        }
    };
private:
    Model();
    /*  current simulation time */
    int time;
    vector<shared_ptr<Seacraft>> seacrafts;
    vector<shared_ptr<Port>> ports;

    /*  returns port by given name  */
    weak_ptr<Port> getPort(const string &portName);

    /*  returns seacraft by given name  */
    weak_ptr<Seacraft> getSeacraft(const string &theName) const;
};


#endif //SEACRAFT_SIMULATION_MODEL_H
