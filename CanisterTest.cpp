/*

#include "Canister.h"
#include "Die.h"
#include <iostream>
#include <list>
#include <cstdlib>

using namespace std;

void printDice(Die **dice);

void printDice(Die **dice)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
            dice[j]->printRow(i);
        cout << endl;
    }
    cout << endl;
}

int main() 
{
    Canister *canister = new Canister();
    Die **group = new Die*[5];
    
    srand(time(NULL));
    
    for(int i = 0; i < 5; i++)
    {
        group[i] = new Die();
        group[i]->roll();
    }
    printDice(group);
    
    list<int> posToRoll;
    posToRoll.push_front(0);
    posToRoll.push_front(1);
    posToRoll.push_front(3);
    
    list<int>::iterator iter;
    for(iter = posToRoll.begin(); iter != posToRoll.end(); ++iter)
        canister->loadDie(group[*iter]);
    
    canister->mix();
    
    printDice(group);
    
    delete canister;
    delete [] group;
    
    return 0;
}

*/