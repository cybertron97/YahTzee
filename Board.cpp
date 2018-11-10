#include "Graph.h"
#include "Board.h"
#include "Scorer.h"
#include "Canister.h"
#include "Hinter.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
// Used to create the Board object.
Board::Board()
{
    // Create all private members.
    group = new Die*[NUM_DICE];
    canister = new Canister();
    scorer = new Scorer();
    setScores = new vector<int>();
    currScores = new list<int>();
    
    // Set all scores to -1.
    for(int i = 0; i < NUM_LABELS; i++)
    {
        currScores->push_front(-1);
        setScores->push_back(-1);
    }
    
    // Create all dice.
    for(int i = 0; i < NUM_DICE; i++)
        group[i] = new Die();
}

// Destructor
// Used to destroy all objects inside of the Board.
Board::~Board()
{
    // Delete all items.
    for(int i = 0; i < 5; i++)
        delete group[i];
    delete [] group;
    
    delete canister;
    delete scorer;
}

// Print()
// Used to print all dice, scores, and labels to the screen.
void Board::print()
{
    // Print all dice first.
    printDiceGroup();
    
    // Print Scorer items afterwards in neat order.
    // Use * to represent scores that are frozen.
    list<int>::iterator currIter = currScores->begin();
    vector<int>::iterator scoreIter = setScores->begin();
    for(int i = 0; i < NUM_LABELS; i++)
    {
        if(i == 6 || i == 7 || i == NUM_LABELS - 1)
            cout << fixed << "    " << right << setw(20) << (LABELS[i] + ": ") 
                 << (*scoreIter != -1 ? *scoreIter : *currIter) 
                 << (*scoreIter != -1 ? "*" : "") << endl;
        else
            cout << fixed << setw(2) << (i < 8 ? (i + 1) : (i - 1)) << ". " 
                 << setw(20) << (LABELS[i] + ": ") << right 
                 << (*scoreIter != -1 ? *scoreIter : *currIter) 
                 << (*scoreIter != -1 ? "*" : "") << endl;
        ++scoreIter;
        ++currIter;
    }
    cout << endl;
}

// TakeTurn()
// Used to take one turn (one dice roll) for the game.
// Makes changes to die in dicePos.
void Board::takeTurn(int *dicePos, int numChanges)
{
    // Load die that need to be change and roll them.
    int i = 0;
    for(i = 0; i < numChanges; i++)
        canister->loadDie(group[dicePos[i]]);
    canister->mix();
    
    // Load the dice into the scorer and find the new scores.
    scorer->loadDice(group);
    loadScores();
}

// SetScore()
// Used to set the score of a particular label such as "4 Of A Kind"
bool Board::setScore(int pos)
{
    // If (after Sixes label)
    // Then add 2 to avoid going into Subtotal or Bonus areas.
    if(pos >= 6)
        pos += 2;
    
    // If a score is already set there, you can't do it and return false.
    // Otherwise, place it into the correct location and return true.
    if(setScores->at(pos) != -1)
        return false;
    else
    {
        list<int>::iterator iter = currScores->begin();
        advance(iter, pos);
        setScores->at(pos) = *iter;
        return true;
    }
}

// GetTotal()
// Used to get the total set score of Yahtzee game.
int Board::getTotal()
{
    return setScores->at(15);
}

// PrintHint()
// Used to get a hint for the current situation (if hints are activated).   
void Board::printHint(int *choices, int size)
{
    // Open up the CPU helper.
    Hinter *cpu = new Hinter();
    
    // Evaluate the choices of possible outcomes from picks
    // that the user provides to change.
    cpu->evaluateChoices(group, choices, size);
    
    // Print out the hints that the CPU has found.
    cpu->printHints();
    
    // Remove it once we're done with it.
    delete cpu;
}

// PrintDiceGroup()
// Used to print all 5 dices next to each other.
void Board::printDiceGroup()
{
    for(int i = 0; i < 5; i++)
    {
        // Print one row of each die.
        for(int j = 0; j < NUM_DICE; j++)
            group[j]->printRow(i);
        cout << endl;
    }
    cout << endl;
}

// LoadScores()
// Used to load the correct values into currScores and setScores.
void Board::loadScores()
{
    // Get scores from Scorer.
    int *scores = scorer->getScoreSheet(), subTotal = -1;
    currScores->clear();
    
    for(int i = 0; i < NUM_LABELS; i++)
    {
        if(i == 6)
        {
            // On Label 6 (Subtotal)
            // Calculate subtotal from previous 0-5 values.
            subTotal = sumItems(0, 6);
            if(subTotal == -1)
                currScores->push_back(-1);
            else
                currScores->push_back(subTotal);
        }
        else if(i == 7)
        {
            // On Label 7 (Bonus)
            // Put bonus in if score >= 63.
            if(subTotal == -1 || subTotal < 63)
                currScores->push_back(-1);
            else
                currScores->push_back(35);
        }
        else
        {
            // All others put into currScores directly.
            if(i < 7)
                currScores->push_back(scores[i]);
            else
                currScores->push_back(scores[i - 2]);
        }
    }
    
    // Total up all setScores for Label 6/7
    // This is for Subtotal and Bonus values.
    int total = 0;
    for(int i = 0; i < 6; i++)
    {
        if(setScores->at(i) > 0)
            total += setScores->at(i);
    }
    setScores->at(6) = total;
    setScores->at(7) = (total >= 63 ? 35 : 0);
    
    // Total up all setScores for Label 15
    // This is for Total total value.
    total = 0;
    for(int i = 6; i < 15; i++)
    {
        if(setScores->at(i) > 0)
            total += setScores->at(i);
    }
    setScores->at(15) = total;
    delete [] scores;
}

// SumItems()
// Returns the sum of the items if they are all finished.
// Otherwise, return -1.
int Board::sumItems(int start, int end)
{
    vector<int>::iterator setIter = setScores->begin();
    advance(setIter, start);
    
    int total = 0;
    for(int i = start; i < end; i++)
    {
        // If any items are not set, then -1.
        if(*setIter == -1)
            return -1;
        else
            total += *setIter;
        ++setIter;
    }
    
    return total;
}