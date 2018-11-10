/*
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "Sort.h"
#include "BinarySearchTree.h"
#include "Graph.h"

using namespace std;

void fill(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

int main()
{
    srand(time(NULL));
    
    int N[] = {10, 20};
    
    for(int i = 0; i < 2; i++) {
        int *values = new int[N[i]];
        fill(values, N[i]);
        Sort::print(values, N[i]);
        Sort::quicksort(values, N[i]);
        Sort::print(values, N[i]);
        delete [] values;

        values = new int[N[i]];
        fill(values, N[i]);
        Sort::print(values, N[i]);
        Sort::mergesort(values, N[i]);
        Sort::print(values, N[i]);
        delete [] values;
    }
    
    BinarySearchTree *tree = new BinarySearchTree();
    
    cout << endl << "ADDED VALUES: ";
    for(int i = 0; i < 10; i++) {
        double num = rand() % 100;
        cout << num << " ";
        tree->insert(num, "TEST");
    }
    cout << endl;
    
    tree->printInOrder();
    delete tree;
    
    EvaluationGraph *graph = new EvaluationGraph(6);
    graph->insert(1, 1);
    graph->insert(1, 1);
    graph->insert(1, 1);
    graph->insert(1, 1);
    graph->insert(2, 3);
    
    cout << "COUNT OF 1: " << graph->numLoops(1) << endl;
    cout << "COUNT OF 2: " << graph->numLoops(2) << endl;
    cout << "DFS CONSECUTIVE: " << graph->strictDFS() << endl;
    
    graph->clear();
    graph->insert(0, 1);
    graph->insert(1, 2);
    graph->insert(2, 3);
    graph->insert(5, 5);
    cout << "COUNT OF 1: " << graph->numLoops(1) << endl;
    cout << "COUNT OF 5: " << graph->numLoops(5) << endl;
    cout << "DFS CONSECUTIVE: " << graph->strictDFS() << endl;
    
    graph->clear();
    graph->insert(0, 1);
    graph->insert(1, 3);
    graph->insert(3, 4);
    graph->insert(4, 5);
    cout << "COUNT OF 1: " << graph->numLoops(3) << endl;
    cout << "COUNT OF 5: " << graph->numLoops(5) << endl;
    cout << "DFS CONSECUTIVE: " << graph->strictDFS() << endl;
    
    return 0;
}
 */