#ifndef POINT_HPP
#define POINT_HPP

// pre-declared to be used as friend
class Graph;

// Point class to be used as a vertex in the Graph adjacency list
class Point{
public:
    Point(int _id, int _distance, int _year)
    : id(_id), 
      distance(_distance),
      year(_year) {}
    
private:
    int id, distance, year;  

friend class Graph;
};

#endif