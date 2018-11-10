/*

#include <cstdlib>
#include <iostream>
#include "Die.h"

using namespace std;

int main() 
{
    Die **dice = new Die*[6];
    srand(time(NULL));
    
    for(int i = 0; i < 6; i++)
    {
        dice[i] = new Die();
        dice[i]->roll();
    }
    
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 6; j++)
            dice[j]->printRow(i);
        cout << endl;
    }
    cout << endl;
    
    for(int i = 0; i < 100; i++)
    {
        int val = dice[0]->roll();
        cout << val << " ";
    }
    cout << endl;
    
    queue<int> history = dice[0]->getHistory();
    while(!history.empty())
    {
        cout << history.front() << " ";
        history.pop();
    }
    cout << endl;
    
    delete [] dice;
   
    return 0;
}

 */