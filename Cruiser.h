//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_CRUISER_H
#define SEACRAFT_SIMULATION_CRUISER_H


#include "Seacraft.h"

class Cruiser : public Seacraft{
public:
    const static int MAX_SPEED = 75;
    const static int DEFAULT_ATTACK_RADIUS = 5;

    Cruiser(const string &craftName, Point point, int strength, float attackRadius=DEFAULT_ATTACK_RADIUS);

    void attack(weak_ptr<Seacraft> seacraft);
    string getClassName() const override;

    string getStatusDetails() const override;

    struct seacraftNotInAttackRadiusException : exception {
        const char * what() const throw() override{
            return "ERROR: Seacraft not in attack radius";
        }
    };
private:
    float attackRadius;
    weak_ptr<Seacraft> toAttack;
public:
    double getMaxSpeed() const override;

public:
    bool isValidSpeed(double speed) const override;

public:
    void update() override;

private:
    bool seacraftIsInAttackRadius(weak_ptr<Seacraft> seacraft);
};


#endif //SEACRAFT_SIMULATION_CRUISER_H
