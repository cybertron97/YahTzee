#ifndef HASHTABLE_H
#define HASHTABLE_H

/* HashTable.h
 * This class is used to represent a HashTable object.
 * Object hashes string values from a Record and places
 * them into a location with their highest score.
 * 
 * This is mainly used for processing by the files and has
 * helped simplify the code inside of the ScoreKeeper class.
 */

// The Include files.
#include <string>
using namespace std;

// Record object.
// Used to store (name, score) information about items in
// the hash table.  
struct Record
{
    // Name and score information in the table.
    string name;
    int score;
    
    // Constructor()
    // Used to make a new Record object.
    Record(string nm, int sc) {
        name = nm;
        score = sc;
    }
};

// HashTable class.
class HashTable
{
    public:
        // Constructor()
        // Used to create a hash table with length size.
        HashTable(int size);
        
        // Destructor()
        // Destroy the entire hash table.
        ~HashTable();
        
        // Update()
        // Either adds a new record with (nm, sc) as values OR
        // modifies the record with sc if it is a better score.
        void update(string nm, int sc);
        
        // Exists()
        // Returns whether name nm exists in the table.
        bool exists(string nm);
       
        // GetScore()
        // Returns the score of the name nm in the table.
        int getScore(string nm);
    
    private:
        // The entire HashTable exists here.
        // Along with number of elements in the table and the size
        // of the table.
        Record **table;
        int numElements, numSize;
        
        // HashFunction()
        // An internal function used to calculate the hash for a value.
        int hashFunction(string word);
        
        // GetLoadFactor()
        // Used to determine how full the table is.
        // Values are 0 <= LF <= 1.
        double getLoadFactor();
        
        // GrowTable()
        // Used to double the size of the table, if space is running out.
        void growTable();
        
        // UpdateHelper()
        // Used as a Helper function to update a table tab with value (nm, sc).
        void updateHelper(Record **tab, string nm, int sc);
        
        // Initialize()
        // Used to empty a table of Records.
        void initialize(Record **tab);
};

#endif /* HASHTABLE_H */