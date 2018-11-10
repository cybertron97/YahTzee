#ifndef BOARD_H
#define BOARD_H

/* Board.h
 * This class is used to represent the Board aspect of the Yahtzee game.
 * This holds 5 Die, a Canister, and Scorer object to do all of the
 * operations.  
 */

// #Include library files.
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Die.h"
#include "Canister.h"
#include "Scorer.h"

using namespace std;

// Number of dice available for Yahtzee game.
const int NUM_DICE = 5;

// Number of labels used for all of the different items on the scorecard.
const int NUM_LABELS = 16;

// The labels for the scorecard.
const string LABELS[] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
                         "Sum", "Bonus", "3 Of A Kind", "4 Of A Kind", 
                         "Full House", "Small Straight", "Large Straight",
                         "Chance", "Yahtzee", "Total Score"};

class Board
{
    public:
        // Constructor
        // Used to create the Board object.
        Board();
        
        // Destructor
        // Used to destroy all objects inside of the Board.
        ~Board();
        
        // Print()
        // Used to print all dice, scores, and labels to the screen.
        void print();
        
        // TakeTurn()
        // Used to take one turn (one dice roll) for the game.
        // Makes changes to die in dicePos.
        void takeTurn(int *dicePos, int numChanges);
        
        // SetScore()
        // Used to set the score of a particular label such as "4 Of A Kind"
        bool setScore(int pos);
        
        // GetTotal()
        // Used to get the total set score of Yahtzee game.
        int getTotal();
        
        // PrintHint()
        // Used to get a hint for the current situation (if hints are activated).
        void printHint(int *choices, int size);
        
    private:
        Die **group; // 5 Dice Used in the Game.
        Canister *canister; // Canister to mix/roll dice.
        Scorer *scorer; // Scorer to do all scoring jobs.
        
        list<int> *currScores; // Current Scores for this turn.
        vector<int> *setScores; // Scores that are already finished.
        
        // PrintDiceGroup()
        // Used to print all 5 dices next to each other.
        void printDiceGroup();
        
        // LoadScores()
        // Used to load the correct values into currScores and setScores.
        void loadScores();
        
        // SumItems()
        // Returns the sum of the items if they are all finished.
        // Otherwise, return -1.
        int sumItems(int start, int end);
        
};

#endif /* BOARD_H */