#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

/* ScoreKeeper.h
 * This class is used to represent the keeper for all scores in the
 * game.  This is to use (username, score) combination in a file
 * and remember it as it goes along (updates when person betters their
 * score.
 */

#include <string>
#include <vector>
#include <iostream>
#include "HashTable.h"

using namespace std;

class ScoreKeeper
{
    public:
        // Constructor
        // Read in all scores to the mapping of information.
        ScoreKeeper();
        
        // Destructor
        // Destroys all structures and saves information to file.
        ~ScoreKeeper();
        
        // UpdateScore()
        // Used to update scores if they are better than previous
        // or add new scores.
        void updateScore(string username, int score);
        
        // PrintScores()
        // Print all scores that are available for this game.
        void printScores();
        
    private:
        HashTable *userScores;   // Hash Table with paired data (username, scores).
        vector<string> *users;   // Vector of just the usernames.
        
        // StoreScores()
        // Used to store information from map to text file scores.txt.
        void storeScores();
};

#endif /* SCOREKEEPER_H */