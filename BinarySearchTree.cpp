#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

// Constructor
// Used to create/initialize a BST.
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
    numItems = 0;
}

// Destructor
// Used to destroy a BST.
BinarySearchTree::~BinarySearchTree()
{
    destroy();
}

// Insert()
// Used to insert a new node (option, score) into tree.
void BinarySearchTree::insert(int sc, string opt)
{
    // Starts the tree at the top with prev before curr.
    Node *curr = root, *prev = NULL;
    
    // While there are elements in the tree to process,
    // Follow the path until the right location.  
    while(curr != NULL) 
    {
        // Set prev to curr.
        prev = curr;
        
        // Move down the right subtree.
        if(sc < curr->opt->score)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    // Tree is null, make this new node the root.
    // If it belongs to the left of root put it there.
    // If it belongs to the right of root put it there.
    if(root == NULL)
        root = new Node(sc, opt, NULL, NULL);
    else if(sc < prev->opt->score)
        prev->left = new Node(sc, opt, NULL, NULL);
    else
        prev->right = new Node(sc, opt, NULL, NULL);
    
    // Increase the number of elements in the tree.
    numItems++;
}

// PrintInOrder()
// Used to do In Order Traversal on this tree.
void BinarySearchTree::printInOrder()
{
    inOrder(root);
    cout << endl;
}

// Destroy()
// Destroys the entire tree.
void BinarySearchTree::destroy()
{
    destroy(root);
    numItems = 0;
    root = NULL;
}

// Size()
// Used to return how many nodes are in the tree.
int BinarySearchTree::size()
{
    return numItems;
}

// Sum()
// Used to return the sum of all nodes in the tree.
// Allows the caller to get expected outcome of data.
int BinarySearchTree::sum()
{
    return sum(root);
}

// Min()
// Used to find the minimum value in the tree.
Option* BinarySearchTree::min()
{
    // Start pointer at the top.
    Node *ptr = root;
    
    // If empty, then no minimum is found.
    if(ptr == NULL)
        return NULL;
    
    // The minimum is the furthest item to the left.
    while(ptr->left != NULL)
        ptr = ptr->left;
    
    // Print out the item that is farthest left.
    return ptr->opt;
}

// Max()
// Used to find the maximum value in the tree.
Option* BinarySearchTree::max()
{
    // Start pointer at the top.
    Node *ptr = root;
    
    // If empty, then no maximum is found.
    if(ptr == NULL)
        return NULL;
    
    // The maximum is the furthest item to the right.
    while(ptr->right != NULL)
        ptr = ptr->right;
    
    // Print out the item that is farthest right.
    return ptr->opt;
}

// Destroy()
// A Helper function that destroys the tree.
void BinarySearchTree::destroy(Node *ptr)
{
    // Do postorder traversal.
    // Go through all children then delete the parent.
    if(ptr != NULL) 
    {
        destroy(ptr->left);
        destroy(ptr->right);
        delete ptr;
    }
}

// InOrder()
// A Helper function that is used to print items in order.
void BinarySearchTree::inOrder(Node *ptr)
{
    // Do inorder traversal.
    // Go through left child, process, then right child.
    if(ptr != NULL) 
    {
        inOrder(ptr->left);
        cout << ptr->opt->score << " " << ptr->opt->opt << endl;
        inOrder(ptr->right);
    }
}

// Sum()
// A helper function that is used to sum items in he tree.
int BinarySearchTree::sum(Node* ptr)
{
    // An empty node is worth 0.
    // An unempty node is this value + all the children.
    if(ptr == NULL)
        return 0;
    else
        return ptr->opt->score + sum(ptr->left) + sum(ptr->right);
}