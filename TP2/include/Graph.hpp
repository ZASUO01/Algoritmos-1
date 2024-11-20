#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Edge.hpp"
#include "Point.hpp"
#include <vector>

// Graph class represented both as an adjacency list of Points and a list of Edges
class Graph{
public:
    Graph(int _n, int _m);                                        // constructor, sets Graph parameters                  
    ~Graph();                                                     // Graph destructor. Free points memory
    void addEdge(int u, int v, int a, int l, int c);              // it adds a new Point to the adjacency list and edge to edges list
    std::vector<long> getMinDistances(int start);                 // Dijkstra algorithm to get the min distances from a start vertex to all the others
    int getMinDistancesYear();                                    // it returns the first year witch the minimum distances can be achieved
    int getConnectionYear();                                      // Kruskal algorithm to get the minimum year in wich the graph is connected
    long getConnectionCost();                                     // Kruskal algorithm to get the minimum cost to connect the graph

private:
    int n, m;                                                     // n: number of vertices, m: number of edges
    int minDistancesYear;                                         // the first year in wich the graph is full connected
    std::vector<Edge *> edges;                                    // list of edges
    std::vector<std::vector<Point* >> adjList;                    // adjacency list
    std::vector<int> parent;                                      // parent list to be used in the Union-Find structure
    std::vector<int> rank;                                        // rank list to be used in the Union-Find structure

    void initTree();                                              // it initializes the parent and rank lists
    int Find(int id, std::vector<int> &parent);                   // it retunrs the parent of a group
    void Union(                                                   // join two groups 
        int a, 
        int b, 
        std::vector<int> &parent, 
        std::vector<int> &rank
    );
};

#endif