#ifndef HINTER_H
#define HINTER_H

/* Hinter.h
 * This class is used to represent a CPU Hinting object.
 * Best used to calculate the subspace and tell the user
 * if their strategy actually makes sense.  Provides information
 * Only when the user has allowed the Hinting.
 */

// Included files.
#include "BinarySearchTree.h"
#include "Scorer.h"
#include "Die.h"
#include <string>
using namespace std;

// The class Hinter
class Hinter
{
    public:
        // Constructor
        // Creates a CPU Hinter
        Hinter();
        
        // Destructor
        // Destroys the CPU Hinter
        ~Hinter();
        
        // EvaluateChoices()
        // Takes a specific set of dice and a set of choices
        // provided by the user and sees the risk/reward of making
        // such a move.  Uses a BST to sort this information out.
        void evaluateChoices(Die **dice, int *choices, int size);
        
        // PrintHints()
        // Prints out the statistical gathered information to the
        // user so they can understand.
        void printHints();
    
    private:
        // The BST used to evaluate the choices.
        // The scorer of information to evaluate each space.
        // A copy of the dice currently in play.
        BinarySearchTree *tree;
        Scorer *scorer;
        Die **copy;
        
        // Original Score of the initial board
        // Choices made by the user and the number of choices made.
        int originalScore, *choices, numChoices;
        
        // EvaluateAll()
        // Helper function to evaluate the current choices.
        void evaluateAll(string strChoice, int level);
        
        // GetScore()
        // Used to get the score of the current play field.
        int getScore(int *sheet, int size);
};

#endif /* HINTER_H */
