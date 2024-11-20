#include "Point.hpp"
#include <cmath>
#include <iostream>


// constructor, initialzes the point info
Point::Point(int _id, int _grade, double _x, double _y){
    this->id = _id;
    this->grade = _grade;
    this->x = _x;
    this->y = _y;
}

// add a new neighbor to the neighbor list, initialy unvisited
void Point::addNeighbor(int nb){
    this->neighbors.push_back({nb, false});
}

// it returns the angle of the line formed by two points
double Point::getLineAngle(Point *pt){
    double deltaY = pt->y - this->y;
    double deltaX = pt->x - this->x;

    double angleInRadians = atan2(deltaY, deltaX);
    double angleInDegrees = angleInRadians * (180 / M_PI);

    if(angleInDegrees < 0) angleInDegrees += 360;

    return angleInDegrees;
}

// it prints the Point info
void Point::print(){
    std::cout << this->id << " ( "<< this->x << ", " << this->y << " ) [ ";

    for(int i = 0; i < grade; i++){
        std::cout << this->neighbors[i].first << " ";
    }
    std::cout << "]\n";
}