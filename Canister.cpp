#include "Canister.h"
#include "Die.h"
#include <iostream>
#include <list>

using namespace std;

// Constructor
// Creates a new canister to hold rollable dice.
Canister::Canister()
{
    group = new list<Die *>();
}

// Destructor
// Removes all dice in this canister.
Canister::~Canister()
{
    delete group;
}

// LoadDie()
// Used to add one Die object into this Canister.
void Canister::loadDie(Die *item)
{
    group->push_back(item);
}

// Mix()
// Used to roll all die in the Canister at the same time.
void Canister::mix()
{
    // Go through all die in list and roll them.
    list<Die *>::iterator iter;
    for(iter = group->begin(); iter != group->end(); ++iter)
        (*iter)->roll();
    
    // Empty Canister out at the end.
    group->clear();
}