#ifndef SCORER_H
#define SCORER_H

/* Scorer.h
 * This class is used to score all dice and see what values can
 * be obtained from this information.  Returns it in a nice
 * array form.
 * 
 * Note: Many changes have been made here because the Graph
 * class has sped up the majority of the solution in this class
 * See all of the private class information how much has changed.
 */

#include <iostream>
#include <list>
#include "Die.h"
#include "Graph.h"

using namespace std;

class Scorer
{
    public:
        // Constructor
        // Creates a Scorer object to grade options.
        Scorer();
        
        // Destructor
        // Destroy all data from this object.
        ~Scorer();
        
        // LoadDice()
        // Load all dice into this Scorer object.
        void loadDice(Die **dice);
        
        // ClearAllScores()
        // Used to start all values at 0.
        void clearAllScores();
        
        // GetScoreSheet()
        // Returns the scoring sheet to be processed by Board.
        int* getScoreSheet();
        
    private:
        list<int> *scoreList;       // Holds a list of scored values.
        EvaluationGraph *graph;     
        int *tray;
        
        // ClearAll()
        // Remove all items in structure.
        void clearAll();
        
        // UpdateValues()
        // Used to update all values of the scored list.
        void updateValues();
        
        // GetValueScore()
        // Gets the score from the specific Die value (2 1's = 2 * 1 = 2).
        int getValueScore(int value);
        
        // GetOAKScore()
        // Gets the score from a specific Of A Kind dice.
        int getOAKScore(int numOAK);
        
        // GetFullHouseScore()
        // Returns 25 if there is a Full House, otherwise 0.
        int getFullHouseScore();
        
        // GetSmallStraightScore()
        // Returns 30 if there is a Small Straight, otherwise 0.
        int getSmallStraightScore();
        
        // GetLargeStraightScore()
        // Returns 40 if there is a Large Straight, otherwise 0.
        int getLargeStraightScore();
        
        // GetChanceScore()
        // Returns Chance score.
        int getChanceScore();
 
        // GetTotalRollScore()
        // Returns the total score of the roll.
        int getTotalRollScore();
};

#endif /* SCORER_H */