#ifndef GRAPH_H
#define GRAPH_H

/* Graph.h
 * This class is used to represent a Graph type object.
 * This approach uses the Adjacency Matrix approach because of its
 * convenience with how it can be accessed.  A mapping of Graph[u,v]
 * means there exists an edge from vertex u to v. 
 * 
 * This class is mostly used as a simpler way to solve the functions
 * in the Scorer class.  As seen in that class, major modifications 
 * have been made there to solve everything in a Graph Algorithms 
 * approach.
 */

// The base class, Graph
class Graph
{
    public:
        // Constructor
        // Creates a graph containing v nodes.
        Graph(int v);
        
        // Destructor
        // Destroy an entire graph.
        ~Graph();
        
        // Insert()
        // Inserts 1 edge inside of this graph from v -> w.
        void insert(int v, int w);
        
        // Clear()
        // Clear the entire graph of edges.
        void clear();
        
        // Outdegree()
        // Determines the outdegree of vertex v, the number of 
        // edges where v is the source.
        int outdegree(int v);
        
        // Indegree()
        // Determines the indegree of vertex v, the number of
        // edges where v is the destination.
        int indegree(int v);
        
    protected:
        // The adjacency matrix for this graph.
        // The number of vertices in the graph.
        int **adjacencyMatrix;
        int numVertices;
};

/* EvaluationGraph
 * This is a derived class from Graph, assuming all of its properties
 * and abilities along with its own.  There are 2 major functions here
 * the ability to count loops and a strict DFS (depth-first search) that
 * solves the Consecutive Order Path problem.
 */

class EvaluationGraph : public Graph
{
    public:
        // Constructor
        // Creates the graph with v vertices.
        EvaluationGraph(int v);
        
        // NumLoops()
        // Finds the number of loops that are at vertex v.
        // Used to find how many OAKs there are for any number.
        int numLoops(int v);
        
        // StrictDFS()
        // Finds a strict Depth-First Search of the graph
        // Strict being that the vertices are in order and are
        // consecutive such as v1, v2, v3, v4 = path of 4.
        // Vertices such as v1, v2, v4, v5 = path of 2.  
        int strictDFS();
    
    private:
        // A visited array for the DFS algorithm.
        bool *visited; 
        
        // StrictDFS()
        // Helper function for finding the strict DFS path.
        int strictDFS(int v);
        
        // PrintMatrix()
        // To be only used by this class for testing.
        // Prints the matrix.
        void printMatrix();
};

#endif