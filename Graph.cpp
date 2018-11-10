#include "Graph.h"
#include <iostream>

using namespace std;

// Constructor
// Creates a graph containing v nodes.
Graph::Graph(int v)
{
    // Create the new adjacency matrix.
    adjacencyMatrix = new int*[v];
    for(int i = 0; i < v; i++) 
    {
        // Initialize each row of the adjacency matrix.
        adjacencyMatrix[i] = new int[v];
        
        // Set each vertex (i,j) to have 0 paths.
        for(int j = 0; j < v; j++)
            adjacencyMatrix[i][j] = 0;
    }
    
    // Set the number of vertices in the graph.
    numVertices = v;
}

// Destructor
// Destroy an entire graph.
Graph::~Graph()
{
    // Go through all rows and destroy the column.
    for(int i = 0; i < numVertices; i++)
        delete [] adjacencyMatrix[i];
        
    // Delete all rows.
    delete [] adjacencyMatrix;
}

// Insert()
// Inserts 1 edge inside of this graph from v -> w.
void Graph::insert(int v, int w)
{
    adjacencyMatrix[v][w]++;
}

// Clear()
// Clear the entire graph of edges.
void Graph::clear()
{
    // Go through all values in the adjacency matrix
    // and change them to 0.
    for(int i = 0; i < numVertices; i++)
        for(int j = 0; j < numVertices; j++)
            adjacencyMatrix[i][j] = 0;
}

// Outdegree()
// Determines the outdegree of vertex v, the number of 
// edges where v is the source.
int Graph::outdegree(int v)
{
    // Start degree at 0.
    int degree = 0;
    
    // Change add degrees when we have edge (v, i).
    for(int i = 0; i < numVertices; i++)
        degree += adjacencyMatrix[v][i];
    
    // Return the degree.
    return degree;
}

// Indegree()
// Determines the indegree of vertex v, the number of
// edges where v is the destination.
int Graph::indegree(int v)
{
    // Start degree at 0.
    int degree = 0;
    
    // Change add degrees when we have edge (i, v).
    for(int i = 0; i < numVertices; i++)
        degree += adjacencyMatrix[i][v];
    
    // Return the degree.
    return degree;
}

// Constructor
// Creates the graph with v vertices.
EvaluationGraph::EvaluationGraph(int v) : Graph(v)
{
    
}

// NumLoops()
// Finds the number of loops that are at vertex v.
// Used to find how many OAKs there are for any number.
int EvaluationGraph::numLoops(int v)
{
    // The number of loops is how many (v, v) edges we have.
    return adjacencyMatrix[v][v];
}

// StrictDFS()
// Finds a strict Depth-First Search of the graph.
int EvaluationGraph::strictDFS()
{
    // Start max at 0.
    int max = 0;
    
    // Initialize visited matrix to all FALSE.
    visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++)
        visited[i] = false;
    
    // Go through each vertex (except the last one)
    // and calculate the strictDFS.
    for(int i = 0; i < numVertices-1; i++)
    {
        // Calculate Path length.
        int path = strictDFS(i);
        
        // If it is a better path, make it max.
        if(path > max)
            max = path;
    }
    
    // Delete visited array.
    delete [] visited;
    
    // Return max.
    return max;
}

// StrictDFS()
// Helper function for finding the strict DFS path.
int EvaluationGraph::strictDFS(int v)
{
    // Set this vertex to visited.
    visited[v] = true;
    
    // If vertex has an edge (v, v+1) and it has
    // not been visited, then continue on with this DFS
    // approach.  Otherwise, end at 1.
    if(v < numVertices - 1 && !visited[v+1] && adjacencyMatrix[v][v+1] > 0)
        return strictDFS(v+1) + 1;
    else
        return 1;
}

// PrintMatrix()
// To be only used by this class for testing.
// Prints the matrix.
void EvaluationGraph::printMatrix()
{
    // Go through all entries of the adjacency matrix
    // and print out elements.
    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
            cout << adjacencyMatrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}