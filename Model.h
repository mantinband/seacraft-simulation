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
enum crafts {
    cruiser,
    freighter,
    patrol_boat,
    invalidCraft
};
class Model {
public:
    Model();
    static Model & getInstance();
    int getTime() const;
    void addCraft(const shared_ptr<Seacraft> &toAdd);
    string getObjectInitialsAt(const Point &p, double scale) const;
    string getStatus() const;
    void addPort(string portName, Point portLocation, double initialFuel, double hourlyFuelProduction);
    void addCraft(const string &craftName, const string &crafType, Point point, int strength, const string &extraInfo);

    void setCourse(string seacraftName, double degree, double speed);
    void setPosition(string seacraftName, Point point, double speed);
    void setDestination(const string &seacraftName,const string &portName, double speed);
    bool seacraftExists(const string &seacraftName) const;
    void addLoadDestination(const string &seacraftName,const string &portDestination);
    void addUnloadDestination(const string &seacraftName,const string &portDestination);
    void setDockingPort(const string &seacraftName,const string &portDestination);
    void refuelCraft(const string &seacraftName);
    void stopSeacraft(const string &seacraftName);

    struct invalidCraftFormat: exception {
        const char * what() const throw() override {
            return "ERROR: Invalid seacraft format. [expected: <name> <type> <coordinates> <strength> (optional: number of containers)";
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
    int time;
    vector<shared_ptr<Seacraft>> seacrafts;
    vector<shared_ptr<Port>> ports;
    crafts getSeacraftType(string s);

    weak_ptr<Port> getPort(const string &portName);

    weak_ptr<Seacraft> getSeacraft(const string &seacraftName) const;
};


#endif //SEACRAFT_SIMULATION_MODEL_H
