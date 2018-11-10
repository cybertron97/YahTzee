/*
#include <iostream>
#include "Hinter.h"
#include "Die.h"

int main()
{
    Die **dice = new Die*[5];
    
    cout << "DICE: ";
    for(int i = 0; i < 5; i++)
    {
        dice[i] = new Die();
        cout << dice[i]->getValue() << " ";
    }
    cout << endl;
    
    int *choices = new int[3];
    choices[0] = 0;
    choices[1] = 4;
    choices[2] = 1;
    
    Hinter *cpu = new Hinter();
    cpu->evaluateChoices(dice, choices, 3);
    cpu->printHints();
    
    return 0;
}
 */