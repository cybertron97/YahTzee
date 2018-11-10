#include "Hinter.h"
#include "Sort.h"
#include "BinarySearchTree.h"
#include "Graph.h"
#include "Scorer.h"
#include <iostream>
#include <string>

// Constructor
// Creates a CPU Hinter
Hinter::Hinter()
{
    // Create objects.
    tree = new BinarySearchTree();
    scorer = new Scorer();
    
    // Create the choices that are chosen by the user.
    // This starts initially empty.
    choices = NULL;
    numChoices = 0;
}

// Destructor
// Destroys the CPU Hinter
Hinter::~Hinter()
{
    delete tree;
    delete scorer;
}

// EvaluateChoices()
// Takes a specific set of dice and a set of choices
// provided by the user and sees the risk/reward of making
// such a move.  Uses a BST to sort this information out.
void Hinter::evaluateChoices(Die **dice, int *choices, int size)
{
    // Destroy any previous tree.
    tree->destroy();
    
    // Create a copy of the entire set of dice.
    copy = new Die*[5];
    for(int i = 0; i < 5; i++)
    {
        copy[i] = new Die();
        copy[i]->set(dice[i]->getValue());
    }
    
    // Sort the dice using Merge Sort.
    Sort::mergesort(choices, size);
    
    // Collect the number of choices from the user's choices.
    // Delete any previous choices made by the user.
    numChoices = size;
    if(this->choices != NULL)
        delete [] this->choices;
    this->choices = new int[size];
        
    string strChoice = "";
    for(int i = 0; i < 5; i++)
    {
        // Go through the entire list of choices
        // And collect only the ones that are not going to be redrawn.
        bool found = false;
        for(int j = 0; j < size; j++)
        {
            // If they are a choice, set found to true.
            if(i == choices[j])
                found = true;
            
            // Hold the choices for later.
            this->choices[j] = choices[j];
        }
        
        // Die was not a choice, then add it to the string with items kept.
        if(!found)
            strChoice = strChoice + " " + static_cast<char>(copy[i]->getValue() + '0');
    }
    
    // Load the dice to the scorer.
    // Score the current set of dice and set the originalScore.
    scorer->loadDice(copy);
    int *sheet = scorer->getScoreSheet();
    originalScore = getScore(sheet, 13);
    
    // Evaluate the sample space at this point (6^numChoices)
    evaluateAll(strChoice, 0);
    
    // Delete all of the copied information
    // as it is not needed any more.
    for(int i = 0; i < 5; i++)
        delete copy[i];
    delete [] copy;
}

// PrintHints()
// Prints out the statistical gathered information to the
// user so they can understand.
void Hinter::printHints()
{
    // Calculate the expected points from the tree.
    // This is an average value (E[x]).
    double points = static_cast<double>(tree->sum()) / tree->size();
    
    // Print the original score to the screen.
    cout << "Original Score is " << originalScore << endl;
    
    // Print the choices taken by the user.
    cout << "Taking choice(s) of ";
    for(int i = 0; i < numChoices; i++)
        cout << (choices[i] + 1) << " ";
    
    // Print out the E[x] value of what is to be returned
    // if this move was made.
    cout << "creates an expected return of ";
    if(points > 0)
        cout << "+";
    cout << points << " points." << endl;
    
    // Show what the best outcome is if they make this move.
    Option *mx = tree->max();
    cout << "Best Outcome:" << mx->opt << " with score change of: ";
    if(mx->score > 0)
        cout << "+";
    cout << mx->score << endl;
    
    // Show what the worst outcome is if they make this move.
    Option *mn = tree->min();
    cout << "Worst Outcome:" << mn->opt << " with score change of: " ;
    if(mn->score > 0)
        cout << "+";
    cout << mn->score << endl;
}

// EvaluateAll()
// Helper function to evaluate the current choices.
void Hinter::evaluateAll(string strChoice, int level)
{
    // If we're at the right level to print to the
    // tree, then evaluate the space and send it to the BST.
    if(numChoices == level)
    {
        // Load dice to the scorer to be evaluated.
        // Calculate the score at this point.
        scorer->loadDice(copy);
        int *sheet = scorer->getScoreSheet();
        
        // Insert the E[x] given there is a change from the original
        // score to the new score.  Negatives are allowed here and are
        // treated correctly by the BST.
        tree->insert(getScore(sheet, 13) - originalScore, strChoice);
    }
    else
    {
        // Go through all die 1-6 in locations that it could
        // replace and see if that space is BETTER.
        for(int i = 1; i <= 6; i++)
        {
            // Set the specific die in the choices array to i.
            copy[choices[level]]->set(i);
            
            // Recursively solve this problem with one less level now.
            evaluateAll(strChoice + " " + static_cast<char>(i + '0'), level + 1);
        }
    }
}

// GetScore()
// Used to get the score of the current play field.
int Hinter::getScore(int *sheet, int size)
{
    // Start score at 0.
    int score = 0;
    
    // Increase the score by the amount the score sheet had.
    for(int i = 0; i < size; i++)
        score += sheet[i];
    
    // Return the score at the end.
    return score;
}
