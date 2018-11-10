#include "ScoreKeeper.h"
#include "HashTable.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Constructor
// Read in all scores to the mapping of information.
ScoreKeeper::ScoreKeeper()
{
    // Open file.
    ifstream inputFile;
    inputFile.open("scores.txt");
    
    // Create HashTable of usernames and scores.
    userScores = new HashTable(100);
    users = new vector<string>();
    
    // If file can open (is available), read all available data points.
    if(inputFile)
    {
        string name;
        int highestScore;
        while(inputFile >> name >> highestScore) 
        {
            // Add records into the hash table and vector.
            userScores->update(name, highestScore);
            users->push_back(name);
        }
    }
}

// Destructor
// Destroys all structures and saves information to file.
ScoreKeeper::~ScoreKeeper()
{
    storeScores();
    delete users;
    delete userScores;
}

// UpdateScore()
// Used to update scores if they are better than previous
// or add new scores.
void ScoreKeeper::updateScore(string username, int score)
{
    // Does the username already exist?
    if(userScores->exists(username))
    {
        // If so, retrieve old score and replace it
        // if the new score is better.
        int high = userScores->getScore(username);
        if(high < score)
            cout << username << ": Your New High Score Is = " << score << endl << endl;
        else
            cout << username << ": Your Game Score Is = " << score << endl << endl;
        userScores->update(username, score);
    }
    else
    {
        // If not found, then add a new record.
        userScores->update(username, score);
        users->push_back(username);
        cout << username << ": Your New High Score Is = " << score << endl << endl;
    }
}

// PrintScores()
// Print all scores that are available for this game.
void ScoreKeeper::printScores()
{
    // Print score list.
    cout << "Score List: " << endl;
    vector<string>::iterator iter = users->begin();
    
    // Go through all elements of map.
    for(int i = 0; i < users->size(); i++)
    {
        string user = (*iter);
        cout << user << " " << userScores->getScore(user) << endl;
        ++iter;
    }
    cout << endl;
}

// StoreScores()
// Used to store information from map to text file scores.txt.
void ScoreKeeper::storeScores()
{
    // Open output file.
    ofstream outFile;
    outFile.open("scores.txt");
    
    // go through all elements and output to the file.
    vector<string>::iterator iter = users->begin();
    for(int i = 0; i < users->size(); i++)
    {
        // Get the user from the vector.
        string user = (*iter);
        
        // Store information about the (user, score) from the hashTable.
        outFile << user << " " << userScores->getScore(user);
        
        // Print end line on all lines except the last.
        if(i < users->size() - 1)
            outFile << endl;
        ++iter;
    }
}