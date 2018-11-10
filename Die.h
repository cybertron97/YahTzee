#ifndef DIE_H
#define DIE_H

/* Die.h
 * This class is used to represent a 6-sided Die (from 1-6).
 */

#include <queue>
#include <stack>
#include <iostream>

using namespace std;

class Die
{
    public:
        // Constructor
        // Used to create a 6-sided Die.
        Die();
        
        // Destructor
        // Used to destroy a 6-sided Die.
        ~Die();
        
        // Roll()
        // Used to roll the die so that it lands on a number from 1-6.
        int roll();
        
        // Set()
        // Used to set the die to a specific value from 1-6.
        void set(int val);

        // GetValue()
        // Gets the value of the die at this moment.
        int getValue();
        
        // GetHistory()
        // Used to retrieve the list of numbers this die has gone through.
        // Returns it as a Queue at the end so that it can be read in order.
        queue<int> getHistory();
        
        // PrintRow()
        // Used to print out one row of information about this Die.
        void printRow(int row);
    
    private:
        // The history numbers this die has rolled.
        // Used as stack to remember only last item rolled.
        stack<int> *history;
};

#endif /* DIE_H */
