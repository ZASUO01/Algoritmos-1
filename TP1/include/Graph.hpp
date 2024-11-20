#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Point.hpp"

// Graph class represented as an adjacency list of Points
class Graph{
public:
    Graph(int _n, int _m);                           // constructor, sets Graph parameters
    ~Graph();                                        // Graph destructor. Free points memory
    void addPoint(Point *p);                         // it adds a new Point to the adjacency list
    std::vector<std::vector<int>> getFaces();        // it returns a list of the Graph faces
    void print();                                    // it prints the Graph adjacency list

private:
    int n;                                           // number of vertices
    int visitedEdges;                                // edges already used in the walk
    int totalEdges;                                  // total number of directed edges (2 * number of edges)
    std::vector<Point*> adjList;                     // Graph adjacency list
    void sortAdjListCLockwise();                     // it sorts all points neighbors in clockwise order of angles in degrees
    void clockwiseDFS(                               // DFS walk in the Graph in the clockwise order of neighbors angles
        int startId, 
        int currentId, 
        int parentId, 
        std::vector<int> &face
    );
};

#endif