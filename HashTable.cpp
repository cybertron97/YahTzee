#include "HashTable.h"

// Constructor()
// Used to create a hash table with length size.
HashTable::HashTable(int size)
{
    // Create table.
    table = new Record*[size];
    
    // Initialize size, elements, and table.
    numSize = size;
    numElements = 0;
    initialize(table);
}

// Destructor()
// Destroy the entire hash table.
HashTable::~HashTable()
{
    delete [] table;
}

// Update()
// Either adds a new record with (nm, sc) as values OR
// modifies the record with sc if it is a better score.
void HashTable::update(string nm, int sc)
{
    // More than 3/4 of the table is full.
    // If so, grow the table by doubling its size.
    if(getLoadFactor() > 0.75)
        growTable();
    
    // Update helper the record (nm, sc).
    updateHelper(table, nm, sc);
}

// Exists()
// Returns whether name nm exists in the table.
bool HashTable::exists(string nm) 
{
    // Calculate the hash of the function.
    int hash = hashFunction(nm);
    
    // While there are elements to still look at in the table.
    while(table[hash] != NULL) 
    {
        // If the hash matches, then return true.
        if(table[hash]->name == nm) 
            return true;
        
        // Move to next element.
        hash = (hash + 1) % numSize;
    }
    
    // If no match is found, return false.
    return false;
}

// GetScore()
// Returns the score of the name nm in the table.
int HashTable::getScore(string nm)
{
    // Calculate the hash of the function.
    int hash = hashFunction(nm);
    
    // While there are elements to still look at in the table.
    while(table[hash] != NULL) 
    {
        // If the hash matches, then return score.
        if(table[hash]->name == nm)
            return table[hash]->score;
        
        // Move to next element.
        hash = (hash + 1) % numSize;
    }
    
    // If no match is found, return -1.
    return -1;
}
       
// HashFunction()
// An internal function used to calculate the hash for a value. 
int HashTable::hashFunction(string word)
{
    // Start sum at 0.
    int sum = 0;
    
    // Use char values from word, cast them to integer
    // And sum them up to form the value to be hashed.
    for(int i = 0; i < word.length(); i++) {
        sum += static_cast<int>(word[i]);
    }
    
    // Hash the sum by the table size.
    return sum % numSize;
}

// GetLoadFactor()
// Used to determine how full the table is.
// Values are 0 <= LF <= 1.
double HashTable::getLoadFactor() 
{
    return numElements / numSize;
}

// GrowTable()
// Used to double the size of the table, if space is running out.
void HashTable::growTable()
{
    // Double the size of the table.
    numSize *= 2;
    
    // Create a new table of double size.
    // Initialize it as well to empty.
    Record **newTable = new Record*[numSize];
    initialize(newTable);
    
    // Go through all elements in the old table 
    for(int i = 0; i < numSize / 2; i++) 
    {
        // If there's a value in the table
        // Then we have to reinsert it into the new table.
        if(table[i] != NULL) 
        {
            // Insert into new table.
            updateHelper(newTable, table[i]->name, table[i]->score);
            
            // Delete old table value.
            delete table[i];
        }
    }
    
    // Delete the old table and set new table.
    delete [] table;
    table = newTable;
}

// UpdateHelper()
// Used as a Helper function to update a table tab with value (nm, sc).
void HashTable::updateHelper(Record **tab, string nm, int sc)
{
    // Hash the value into the appropriate location.
    int hash = hashFunction(nm);
    
    // If some value exists and it is this item nm we're looking forr
    // then we may need to update it.
    if(tab[hash] != NULL && tab[hash]->name == nm) 
    {
        // Update it only if the value of the score is better
        // than what is previously there.
        if(tab[hash]->score < sc)
            tab[hash]->score = sc;
    }
    else 
    {
        // Otherwise use Linear Probing to find the right hash 
        // location.
        while(tab[hash] != NULL)
            hash = (hash + 1) % numSize;
        
        // Store new record into table's hash value.
        // Increase the number of elements inside of it by 1.
        tab[hash] = new Record(nm, sc);
        numElements++;
    }
}

// Initialize()
// Used to empty a table of Records.
void HashTable::initialize(Record **tab)
{
    // Go through all elements in table and set it to NULL.
    for(int i = 0; i < numSize; i++)
        tab[i] = NULL;
}