//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_CRUISER_H
#define SEACRAFT_SIMULATION_CRUISER_H


#include "Seacraft.h"
#include "SeacraftFactory.h"
/*****************************************************/
/*  Class represents a pirate-ship.                  */
/*  pirate ship can attack a Freighter and take its  */
/*  containers,or attack a patrol boat and harm it's */
/*  resistance. it cannot dock at a port, or refuel. */
/*****************************************************/

class Cruiser : public Seacraft{
public:
    const static int MAX_SPEED = 75;
    const static int DEFAULT_ATTACK_RADIUS = 5;

    Cruiser(const string &craftName, Point point, int strength, float attackRadius=DEFAULT_ATTACK_RADIUS);

    /*  attack given seacraft on next update    */
    void attack(weak_ptr<Seacraft> seacraft);

    /*  returns class name: "Cruiser"  */
    string getClassName() const override;

    /*  returns string with details regarding
     *  ship's status. location, resistance etc'    */
    string getStatusDetails() const override;

    /*  returns fuel consumption. NOT IMPLEMENTED FOR CRUISER   */
    double getFuelConsumption() const override;

    /*  refuel request. NOT IMPLEMENTED FOR CRUISER */
    void refuel(weak_ptr<Seacraft> ptr) override;

    /*  returns ship's max speed    */
    double getMaxSpeed() const override;

    /*  returns true if given speed is valid. false otherwise.  */
    bool isValidSpeed(double speed) const override;

    /*  updates ships location and attacks ship if an attack request was set    */
    void update() override;

    struct seacraftNotInAttackRadiusException : exception {
        const char * what() const throw() override{
            return "ERROR: Seacraft not in attack radius";
        }
    };

    struct fuelNotSupportedException : exception{
        const char * what() const throw() override{
            return "ERROR: Cruiser does not support fuel actions ";
        }
    };
private:
    float attackRadius;
    weak_ptr<Seacraft> toAttack;

    /*  returns true if seacraft is in ships attack radius. false otherwise */
    bool seacraftIsInAttackRadius(weak_ptr<Seacraft> seacraft);
    static RegisterSeacraft registerSeacraft;
    static shared_ptr<Seacraft> createCruiser(const string &data);
};


#endif //SEACRAFT_SIMULATION_CRUISER_H
