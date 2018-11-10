#ifndef CANISTER_H
#define CANISTER_H

/* Canister.h
 * This class is used to represent the Dice to be rolled on each turn.
 * You can load, mix, and get any dice that you want.
 */

#include "Die.h"
#include <iostream>
#include <list>

using namespace std;

class Canister
{
    public:
        // Constructor
        // Creates a new canister to hold rollable dice.
        Canister();
        
        // Destructor
        // Removes all dice in this canister.
        ~Canister();
        
        // LoadDie()
        // Used to add one Die object into this Canister.
        void loadDie(Die *item);
        
        // Mix()
        // Used to roll all die in the Canister at the same time.
        void mix();
        
    private:
        list<Die *> *group; // The list of all die to be rolled.
};

#endif /* CANISTER_H */