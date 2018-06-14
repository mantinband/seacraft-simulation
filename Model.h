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
    void addCraft(const string &craftName, Point point, int strength, const string &extraInfo);

    struct invalidCraftFormat: exception {
        const char * what() const throw() override {
            return "ERROR: Invalid seacraft format. [expected: <name> <type> <coordinates> <strength> (optional: number of containers)";
        }
    };

private:
    vector<shared_ptr<Seacraft>> seacrafts;
    vector<shared_ptr<Port>> ports;
    int time;
    crafts getSeacraftType(string s);

    void addCraft(const string &craftName, const string &crafType, Point point, int strength, const string &extraInfo);
};


#endif //SEACRAFT_SIMULATION_MODEL_H
