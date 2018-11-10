#include "Die.h"
#include <queue>
#include <stack>
#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor
// Used to create a 6-sided Die.
Die::Die()
{
    history = new stack<int>();
    roll();
}

// Destructor
// Used to destroy a 6-sided Die.
Die::~Die()
{
    delete history;
}

// Roll()
// Used to roll the die so that it lands on a number from 1-6.
int Die::roll()
{
    int value = (rand() % 6) + 1;
    history->push(value);
    return value;
}

// Set()
// Used to set the die to a specific value from 1-6.
void Die::set(int val)
{
    history->push(val);
}

// GetValue()
// Gets the value of the die at this moment.
int Die::getValue()
{
    return history->top();
}

// GetHistory()
// Used to retrieve the list of numbers this die has gone through.
// Returns it as a Queue at the end so that it can be read in order.
queue<int> Die::getHistory()
{
    stack<int> tempStack;
    queue<int> historyQueue;
    
    // Push all items in history to temporary stack (from last to first)
    while(!history->empty())
    {
        tempStack.push(history->top());
        history->pop();
    }
    
    // Then store to Queue from the first item to last.
    // And store back to History stack to regain order.
    while(!tempStack.empty())
    {
        historyQueue.push(tempStack.top());
        history->push(tempStack.top());
        tempStack.pop();
    }
    
    // Return the queue.
    return historyQueue;
}

// PrintRow()
// Used to print out one row of information about this Die.
void Die::printRow(int row)
{
    int currVal = getValue();
    
    // Go through each column of this die.
    for(int j = 0; j < 5; j++)
    {
        if(row == 0 || row == 4)
        {
            // Outer top or bottom wall.
            if(j != 0 && j != 4)
                cout << "-";
            else
                cout << " ";
        }
        else if(j == 0 || j == 4)
        {
            // Outer left or right wall.
            if(row != 0 && row != 4)
                cout << "|";
            else
                cout << " ";
        }
        // All of the pips on the die.
        else if(((row == 1 && j == 1) || (row == 3 && j == 3)) && currVal >= 2)
            cout << "o";
        else if(((row == 1 && j == 3) || (row == 3 && j == 1)) && currVal >= 4)
            cout << "o";
        else if(row == 2 && (j == 1 || j == 3) && currVal == 6)
            cout << "o";
        else if(row == 2 && j == 2 && currVal % 2 == 1)
            cout << "o";
        // All others, blank spot.
        else
            cout << " ";
    }
    cout << " ";
}