#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

/* BinarySearchTree.h
 * This class is used to represent a BST type object that holds values 
 * called Options for specific set of dice information and their total
 * score.  Does operations like a normal BST tree.
 */

// #Include library files.
#include <string>
#include <vector>

using namespace std;

// An Option object.
// Holds information about space such as (1,2,3,4,5) for dice information
// And then holds a score card value from this space.  Items in BST are
// ordered by score.
struct Option 
{
    int score;
    string opt;
    
    // Constructor for an Option object.
    Option(int sc, string op) {
        score = sc;
        opt = op;
    }
};

// A Node object.
// Holds content for a BST.  Each node has a value (Option) and
// a left and right pointer.  The left pointer holds a space that
// is less in score than this one and the right pointer holds a space
// that is higher in score than this one.
struct Node
{
    // Items in a Node object.
    Option *opt;
    Node *left, *right;
    
    // Constructor for a Node object.
    Node(int score, string option, Node *lf, Node *rt) {
        opt = new Option(score, option);
        left = lf;
        right = rt;
    }
};

// Binary Search Tree Definition.
class BinarySearchTree
{
    public:
        // Constructor
        // Used to create/initialize a BST.
        BinarySearchTree();
        
        // Destructor
        // Used to destroy a BST.
        ~BinarySearchTree();
        
        // Insert()
        // Used to insert a new node (option, score) into tree.
        void insert(int sc, string opt);
        
        // PrintInOrder()
        // Used to do In Order Traversal on this tree.
        void printInOrder();
        
        // Destroy()
        // Destroys the entire tree.
        void destroy();
        
        // Size()
        // Used to return how many nodes are in the tree.
        int size();
        
        // Sum()
        // Used to return the sum of all nodes in the tree.
        // Allows the caller to get expected outcome of data.
        int sum();
        
        // Min()
        // Used to find the minimum value in the tree.
        Option* min();
        
        // Max()
        // Used to find the maximum value in the tree.
        Option* max();
    
    private:
        // The pointer to the tree and the number of items in it.
        Node *root;
        int numItems;
        
        // Destroy()
        // A Helper function that destroys the tree.
        void destroy(Node *ptr);
        
        // InOrder()
        // A Helper function that is used to print items in order.
        void inOrder(Node *ptr);
        
        // Sum()
        // A helper function that is used to sum items in he tree.
        int sum(Node *ptr);
};

#endif /* BINARYSEARCHTREE_H */