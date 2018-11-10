
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Board.h"
#include "ScoreKeeper.h"

using namespace std;

// GetInputs()
// Used to change a string form of inputs ("1 2 3 4") into vector 1,2,3,4
vector<int>* getInputs(string strInput);

// Act()
// Used to do one round of Yahtzee to the player.
void act(Board *board, bool hintFlag);

// PlayGame()
// Plays one game of Yahtzee to the player.
void playGame(ScoreKeeper *keeper, bool hintFlag);

// PrintMenu()
// Print menu of options to the screen.
void printMenu();

// GetInputs()
// Used to change a string form of inputs ("1 2 3 4") into vector 1,2,3,4
vector<int>* getInputs(string strInput)
{
    // Create vector of positions.
    vector<int> *positions = new vector<int>();
    
    // Go through vector of inputs.
    for(int i = 0; i < strInput.length(); i++)
    {
        // Change '1' to '5' to 1 to 5.
        int pos = strInput[i] - '0';
        
        // If values are valid, add them to vector.
        if(pos >= 1 && pos <= 5)
            positions->push_back(pos - 1);
        else if(strInput[i] != ' ' && strInput[i] != '\n' && strInput[i] != '\0')
        {
            // If there is a bad character other than 1-5, space, endline, or
            // null char, then return NULL for bad input.
            delete positions;
            return NULL;
        }
    }
    
    // Return positions.
    return positions;
}

// Act()
// Used to do one round of Yahtzee to the player.
void act(Board *board, bool hintFlag)
{
    int numItems = 5;
    char response = 'y';
    
    // Get initial die positions to roll.
    int *diePos = new int[numItems];
    for(int i = 0; i < 5; i++)
        diePos[i] = i;
            
    for(int turn = 1; turn <= 3; turn++)
    {
        // Roll the dice for this turn.
        board->takeTurn(diePos, numItems);
        
        // Print outcome.
        board->print();
        cout << "Turn #" << turn << endl;
        if(turn != 3)
        {
            // If we have a hint to give, then do this.
            // It's the same code for replacement.
            if(hintFlag)
            {
                cout << "Do you want a hint? (y/n): ";
                cin >> response;
                if(response == 'y' || response == 'Y')
                {
                    cin.ignore(100, '\n');

                    string strInput;
                    vector<int> *positions = NULL;

                    // Ask user for positions to replace.
                    cout << "Enter all die positions (1-5) separated by spaces to replace: ";
                    getline(cin, strInput);
                    positions = getInputs(strInput);

                    // If bad positions, then make user try again.
                    while(positions == NULL)
                    {
                        cout << "Error: Bad positions, try again: ";
                        getline(cin, strInput);
                        positions = getInputs(strInput);
                    }

                    // Load which positions to change.
                    if(diePos != NULL)
                        delete [] diePos;
                    diePos = new int[positions->size()];
                    for(int i = 0; i < positions->size(); i++)
                        diePos[i] = positions->at(i);
                    numItems = positions->size();

                    // Print the hint here to the user.
                    board->printHint(diePos, numItems);
                    
                    delete positions;
                }
            }
            // Ask if user wants to replace any die.
            cout << "Do you want to replace any die? (y/n): ";
            cin >> response;
            if(response == 'y' || response == 'Y')
            {
                cin.ignore(100, '\n');
                
                string strInput;
                vector<int> *positions = NULL;
                
                // Ask user for positions to replace.
                cout << "Enter all die positions (1-5) separated by spaces to replace: ";
                getline(cin, strInput);
                positions = getInputs(strInput);
                
                // If bad positions, then make user try again.
                while(positions == NULL)
                {
                    cout << "Error: Bad positions, try again: ";
                    getline(cin, strInput);
                    positions = getInputs(strInput);
                }

                // Load which positions to change.
                delete [] diePos;
                diePos = new int[positions->size()];
                for(int i = 0; i < positions->size(); i++)
                    diePos[i] = positions->at(i);
                numItems = positions->size();
                
                delete positions;
            }
            else 
            {
                delete [] diePos;
                break;
            }
        }
        else
            delete [] diePos;
    }
    
    // Let user choose which item should get this score.
    int choice;
    cout << "Enter the specific item to confirm score (1-13): ";
    cin >> choice;
    
    // If item scored is bad (not 1-13), then error and try again.
    // Or item is already used up, then try again.
    while(!board->setScore(choice - 1) || choice < 1 || choice > 13)
    {
        if(choice < 1 || choice > 13)
            cout << "Error: That choice is invalid, use (1-13)." << endl;
        else
            cout << "Error: That choice is already used." << endl;
        cout << "Re-enter another choice to confirm score (1-13): ";
        cin >> choice;
    }
}

// PlayGame()
// Plays one game of Yahtzee to the player.
void playGame(ScoreKeeper *keeper, bool hintFlag) 
{
    Board *board = new Board();
    
    // Ask user for nickname.
    string name;
    cout << "Enter your nickname (1 word only): ";
    cin >> name;
    
    // Perform game.
    for(int i = 0; i < 13; i++)
        act(board, hintFlag);
    
    // Update score if possible.
    keeper->updateScore(name, board->getTotal());
    
    delete board;
}

// PrintMenu()
// Print menu of options to the screen.
void printMenu(bool giveHints)
{
    cout << "----------------------------" << endl;
    cout << " 1. Play Yahtzee Game       " << endl;
    cout << " 2. See Scores              " << endl;
    if(giveHints)
        cout << " 3. Turn Off Hints       " << endl;
    else
        cout << " 3. Turn On Hints       " << endl;
    cout << " 4. Quit                    " << endl;
    cout << "----------------------------" << endl;
}

// Main()
int main()
{
    // Create scorer.
    ScoreKeeper *keeper = new ScoreKeeper();
    int choice;
    bool hintFlag = false;
        
    // Randomly create RNG.
    srand(time(NULL));
    
    // Welcome message.
    cout << "Welcome to the Yahtzee Game!" << endl;
    
    do
    {
        // Print Menu
        // Get choice to do.
        printMenu(hintFlag);
        cout << "Enter Choice > ";
        cin >> choice;

        // If bad input, then make user try again.
        while(choice < 1 || choice > 4)
        {
            cout << "Error: Bad Choice, re-enter choice (1-3) > ";
            cin >> choice;
        }
        cout << endl;

        // Choose the option, 1, 2, or 3.
        switch(choice)
        {
            case 1:
                playGame(keeper, hintFlag);
                break;
            case 2:
                keeper->printScores();
                break;
            case 3: 
                hintFlag = !hintFlag;
                cout << "Hints are turned " << (hintFlag ? "ON" : "OFF") << endl << endl;
                break;
            case 4:
                break;
        }
    } while (choice != 4);
    
    // Destroy object at the end.
    delete keeper;
    
    // End Program.
    return 0;
}