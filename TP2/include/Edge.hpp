#ifndef EDGE_HPP
#define EDGE_HPP

// pre-declared to be used as friend
class Graph;

// Edge class to be used in the Graph edges list
class Edge{
public:
    Edge(int _u, int _v, int _year, int _cost)
        : u(_u), 
          v(_v), 
          year(_year),  
          cost(_cost){};

private:
    int u, v, year, cost; 

friend class Graph;
};

#endif