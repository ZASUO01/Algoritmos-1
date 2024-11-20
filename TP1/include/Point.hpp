#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#include <utility>

class Graph; // pre-declared to be used as friend

// Point 2D class to be used as a Graph vertex
class Point{
public:
    Point(int _id, int grade, double _x, double _y);    // constructor, initialzes the point info
    void addNeighbor(int nb);                           // add a new neighbor to the neighbor list, initialy unvisited
    void print();                                       // it prints the Point info

private:
    int id;                                             // Point int identifier
    int grade;                                          // number of neighbors 
    double x, y;                                        // Point coordinates 
    std::vector<std::pair<int, bool>> neighbors;        // list of neighbors. It represents directed edges from this Point to the neighbor {id, visited}
    double getLineAngle(Point *pt);                     // it returns the angle of the line formed by two Points 

    friend class Graph; 
};

#endif