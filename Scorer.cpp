#include "Scorer.h"
#include "Die.h"
#include "Sort.h"
#include "Graph.h"
#include <iostream>
#include <list>
#include <iterator>

using namespace std;

// Constructor
// Creates a Scorer object to grade options.
Scorer::Scorer()
{
    // Create objects of this class.
    scoreList = new list<int>();
    graph = new EvaluationGraph(6);
    
    // Clear all values.
    clearAllScores();
}

// Destructor
// Destroy all data from this object.
Scorer::~Scorer()
{
    delete scoreList;
    delete graph;
}

// LoadDice()
// Load all dice into this Scorer object.
void Scorer::loadDice(Die **dice)
{
    // Clear all structures.
    clearAll();
    
    // Create the tray of dice used by the scorer for
    // this situation.
    tray = new int[5];
    for(int i = 0; i < 5; i++)
        tray[i] = dice[i]->getValue() - 1;
    
    // Quicksort the entire tray so that it can do the graph
    // algorithm efficiently.
    Sort::quicksort(tray, 5);
    
    // **Important**
    // Insert into the graph edges of adjacent elements inside of the
    // tray of dice.  If a tray contains 1,1,1,2,3 then create a circular
    // link from (1,1) then (1,1) then (1,2) then (2,3) and finally (3,1)
    // This sets up the entire graph so that loops count the exact number
    // of OAKs and the strictDFS can calculate a straight.
    for(int i = 0; i < 4; i++)
        graph->insert(tray[i], tray[i+1]);
    graph->insert(tray[4], tray[0]);
}

// ClearAllScores()
// Used to start all values at 0.
void Scorer::clearAllScores()
{
    scoreList->clear();
    
    // Clear scoreList.
    for(int i = 0; i < 13; i++)
        scoreList->insert(scoreList->end(), 0);
}

// GetScoreSheet()
// Returns the scoring sheet to be processed by Board.
int* Scorer::getScoreSheet()
{
    int *sheet = new int[13];
    int i = 0;
    
    // Update scorer items in the list.
    updateValues();
    
    // Move list items to the integer array.
    list<int>::iterator iter;
    for(iter = scoreList->begin(); iter != scoreList->end(); ++iter)
    {
        sheet[i] = *iter;
        i++;
    }
    
    return sheet;
}

// UpdateValues()
// Used to update all values of the scored list.
void Scorer::updateValues()
{
    int i = 0, score;
    
    // Go through entire list of items to score.
    list<int>::iterator iter;
    for(iter = scoreList->begin(); iter != scoreList->end(); i++)
    {
        // Remove previous scores.
        iter = scoreList->erase(iter);
        
        // Calculate all scores for 13 values.
        switch(i)
        {
            case 0: score = getValueScore(1);
                break;
            case 1: score = getValueScore(2);
                break;
            case 2: score = getValueScore(3);
                break;
            case 3: score = getValueScore(4);
                break;
            case 4: score = getValueScore(5);
                break;
            case 5: score = getValueScore(6);
                break;
            case 6: score = getOAKScore(3);
                break;
            case 7: score = getOAKScore(4);
                break;
            case 8: score = getFullHouseScore();
                break;
            case 9: score = getSmallStraightScore();
                break;
            case 10: score = getLargeStraightScore();
                break;
            case 11: score = getChanceScore();
                break;
            case 12: score = getOAKScore(5);
                break;
        }
        
        // Reinsert new score.
        scoreList->insert(iter, score);
    }
}

// ClearAll()
// Remove all items in structure.
void Scorer::clearAll()
{
    // Clear graph
    graph->clear();
}
        
// GetValueScore()
// Gets the score from the specific Die value (2 1's = 2 * 1 = 2).
int Scorer::getValueScore(int value)
{
    // The indegree of a node in a graph tells how many of a
    // specific number there are. 
    return value * (graph->indegree(value - 1));
}

// GetOAKScore()
// Gets the score from a specific Of A Kind dice.
int Scorer::getOAKScore(int numOAK)
{
    // Go through all dice possibilities (1-6)
    for(int i = 0; i < 6; i++) 
    {
        // Does dice value i have enough loops to
        // make the right amount of OAK?
        if(graph->numLoops(i) >= numOAK - 1) 
        {
            // If so then return 50 if exactly 5.
            // Otherwise it's the total score.
            if(numOAK == 5)
                return 50;
            else
                return getTotalRollScore();
        }
    }
    
    // Otherwise no OAK.
    return 0;
}

// GetFullHouseScore()
// Returns 25 if there is a Full House, otherwise 0.
int Scorer::getFullHouseScore()
{
    // Set flags for 2OAK and 3OAK to false.
    bool has2OAK = false, has3OAK = false;
    
    // Go through each die number (1-6)
    for(int i = 0; i < 6; i++) 
    {
        // Do we have a 2OAK or 3OAK based on the number
        // of loops on die value i in the graph?
        has2OAK = has2OAK || (graph->numLoops(i) == 1);
        has3OAK = has3OAK || (graph->numLoops(i) == 2);
    }
    
    // If both exist then return 25, otherwise 0.
    return (has2OAK && has3OAK) ? 25 : 0;
}

// GetSmallStraightScore()
// Returns 30 if there is a Small Straight, otherwise 0.
int Scorer::getSmallStraightScore()
{
    // If strictDFS returns 4 as a length
    // then we have a small straight and return 30
    // otherwise 0.
    return ((graph->strictDFS() >= 4) ? 30 : 0);
}

// GetLargeStraightScore()
// Returns 40 if there is a Large Straight, otherwise 0.
int Scorer::getLargeStraightScore()
{
    // If strictDFS returns 5 as a length
    // then we have a small straight and return 40
    // otherwise 0.
    return ((graph->strictDFS() == 5) ? 40 : 0);
}

// GetChanceScore()
// Returns Chance score.
int Scorer::getChanceScore()
{
    return getTotalRollScore();
}

// GetTotalRollScore()
// Returns the total score of the roll.
int Scorer::getTotalRollScore()
{
    // Total sum starts at 0.
    int sum = 0;
    
    // Sum up the values on the die.
    for(int i = 0; i < 5; i++) 
        sum += (tray[i] + 1);
    
    // Return the sum.
    return sum;
}