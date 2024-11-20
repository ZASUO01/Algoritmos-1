#include "Graph.hpp"
#include <algorithm>

// constructor, sets Graph parameters
Graph::Graph(int _n, int _m){
    this->n = _n;                   
    this->visitedEdges = 0;        
    this->totalEdges = 2 * _m;      
}

// Graph destructor. Free points memory
Graph::~Graph(){
    for(auto ptr : adjList){
        delete ptr;
    }
}

// it adds a new Point to the adjacency list
void Graph::addPoint(Point *p){
    this->adjList.push_back(p);
}

// it prints the Graph adjacency list
void Graph::print(){
    for(int i = 0; i < n; i++){
        this->adjList[i]->print();
    }
}

// it sorts all points neighbors in clockwise order of angles in degrees
void Graph::sortAdjListCLockwise(){
    //auxiliar vector that stores the neighbor id and the line angle
    std::vector<std::pair<int, double>> aux;
    
    // for each point in the adj list
    for(int i = 0; i < n; i++){
        Point *p1 = adjList[i];
        int nbSize = p1->grade;
        aux.reserve(nbSize);
        int j;

        // for each neighbor of that point
        for(j = 0; j < nbSize; j++){
            int p2Id = p1->neighbors[j].first;
            Point *p2 = adjList[p2Id - 1];

            //get the angle formed by that point and the current neighbor
            double angle = p1->getLineAngle(p2);
            aux.emplace_back(p2->id, angle);
        }

        // sort the aux vector in descendent order of angles (clockwise)
        std::sort(aux.begin(), aux.end(), [](const auto &p1, const auto &p2){
            return p1.second > p2.second;
        });

        // update the Point neighbor list with the new order
        for(j = 0; j < nbSize; j++){
            p1->neighbors[j].first = aux[j].first;
        }

        aux.clear();
    }
}

// DFS walk in the Graph in the clockwise order of neighbors angles
void Graph::clockwiseDFS(int startId, int currentId, int parentId, std::vector<int> &face){
    int i, nbSize;
    
    // add the current id to the faces
    face.push_back(currentId);

    Point *current = adjList[currentId - 1];
    nbSize = current->grade;

    // stop condition when the starter point is found again
    // check if the right next edge of the parent is already visited to finish the cycle
    if(currentId == startId){
        int arcCounter = 0;

        //the right next neighbour of the parent should not be unvisited to finish the recursion
        for(i = 0; i < nbSize; i++){
            if(current->neighbors[i].first == parentId){
                bool neighborVisited;
                
                if(i == nbSize - 1) neighborVisited = current->neighbors[0].second;
                else neighborVisited = current->neighbors[i+1].second;
                
                if(!neighborVisited) arcCounter++;
            }
        }
        if(arcCounter == 0){
            return;
        }
    }
    
    //next neighbor id
    int nextId;

    // look for the parent in the current neighbours list
    for(int i = 0; i < nbSize; i++){
        int neighborId = current->neighbors[i].first;
        
        // if the parent is found then take the right next point in the neighbours list
        if(neighborId == parentId){
            // case the index is the last, take the first
            if(i == nbSize - 1){
                nextId = current->neighbors[0].first;
                current->neighbors[0].second = true;
            }
            // take the right next otherwise
            else{
                nextId = current->neighbors[i + 1].first;
                current->neighbors[i + 1].second = true;
                i = nbSize;
            }

            // increase the total number of visited edges
            this->visitedEdges++;
        }
    }

    clockwiseDFS(startId, nextId, currentId, face);
}

// it returns a list of the Graph faces
std::vector<std::vector<int>> Graph::getFaces(){
    std::vector<std::vector<int>> faces;

    // it depends on the sorted adj list to build the faces
    this->sortAdjListCLockwise();

    // for each point in the adj list
    for(int i = 0; i < this->n; i++){
        Point *start = this->adjList[i];
        int startNbSize = start->grade;
        int startId = start->id;
        
        std::vector<int> face;

        // for each neighbour of that point
        for(int j = 0; j < startNbSize; j++){
            bool visited = start->neighbors[j].second;

            // if it's not visited yet then start the DFS walk
            if(!visited){
                // add start point to the face
                face.push_back(startId);
                
                // mark this neighbour as visited
                start->neighbors[j].second = true;

                // increase the total number of visited edges
                this->visitedEdges++;

                // start the DFS walk from the neighbour
                int neighborId = start->neighbors[j].first;
                clockwiseDFS(startId, neighborId, startId, face);

                // push the face to the solution and reset the current face
                faces.push_back(face);
                face.clear();   
            }

            // optimization. If all edges are visited, there's no needing to continue
            if(this->visitedEdges == this->totalEdges){
                j = startNbSize;
                i = this->n;
            }
        }
    }

    return faces;
}
