#include "Graph.hpp"
#include <queue>
#include <utility>
#include <climits>
#include <algorithm>

// constructor, sets Graph parameters 
Graph::Graph(int _n, int _m){
    this->n = _n;
    this->m = _m;
    this->minDistancesYear = 0;

    adjList = std::vector<std::vector<Point *>>(_n + 1, std::vector<Point*>());
    parent = std::vector<int>(_n + 1);
    rank = std::vector<int>(_n + 1);
}

// Graph destructor. Free points memory
Graph::~Graph(){
    for(auto ptr : edges){
        delete ptr;
    }

    for(auto lst : adjList){
        for(auto ptr: lst){
            delete ptr;
        }
    }
}

// it adds a new Point to the adjacency list and edge to edges list
void Graph::addEdge(int u, int v, int a, int l, int c){
    Edge *ed1 = new Edge(u, v, a, c);
    Edge *ed2 = new Edge(v, u, a, c);

    edges.push_back(ed1);
    edges.push_back(ed2);

    Point *p1 = new Point(v, l, a);
    Point *p2 = new Point(u, l, a);

    adjList[u].push_back(p1);
    adjList[v].push_back(p2);
}

// Dijkstra algorithm to get the min distances from a start vertex to all the others
std::vector<long> Graph::getMinDistances(int start){
    // Minimun distances list
    std::vector<long> minDistances(this->n + 1, LONG_MAX);
    minDistances[start] = 0;

    // list of minimum year that a vertex can be accessed
    std::vector<long> minYears(this->n + 1, 0);

    // priority queue for BFS
    std::priority_queue<std::pair<long, int>, std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> pq;
    pq.push({0, start});
    
    // while there are unchecked vertices
    while(!pq.empty()){
        // get the top one
        std::pair<long, int> u = pq.top();
        pq.pop();
    
        long uDistance = u.first;
        int uId = u.second;

        // optimization to avoid useless iteration
        if(uDistance > minDistances[uId]) continue;
        
        // for each neighbor of u
        for(const Point *p : this->adjList[uId]){
            int vId = p->id;
            long vDistance = p->distance + minDistances[uId];
            int vYear = p->year;

            // if the edge can be reduced, then reduce it and add v to the queue
            // also define the min year to acess that v
            if(minDistances[vId] > vDistance){
                minDistances[vId] = vDistance;
                pq.push({vDistance, vId});
                minYears[vId] = vYear;
            }
            //If it can't be reduced by there's a shorter year value then do the same
            else if(minDistances[vId] == vDistance && vYear < minYears[vId]){
                pq.push({vDistance, vId});
                minYears[vId] = vYear;
            }
        }
    }

    //it sets the graph min distances year by taking the greater year of the list
    for(int i = 1; i <= this->n; i++){
        if(i != start && minYears[i] > this->minDistancesYear) this->minDistancesYear = minYears[i];
    }
    
    return minDistances;
}

// it returns the first year witch the minimum distances can be achieved
int Graph::getMinDistancesYear(){
    return this->minDistancesYear;
}
                                                    
// it initializes the parent and rank lists
void Graph::initTree(){
    for(int i = 0; i <= this->n; i++){
        this->parent[i] = i;
        this->rank[i] = 1;
    }
}

// it retunrs the parent of a group
int Graph::Find(int id, std::vector<int> &parent){
    if(parent[id] == id) return id;
    return Find(parent[id], parent);
}

// it joins two groups
void Graph::Union(int a, int b, std::vector<int> &parent, std::vector<int> &rank){
    if(rank[a] < rank[b]){
        parent[a] = b;
        rank[b]++;
    }
    else{
        parent[b] = a;
        rank[a]++;
    }
}

// Kruskal algorithm to get the minimum year in wich the graph is connected
int Graph::getConnectionYear(){
    // initialize Union-Find structure
    initTree();
    
    // sort edges by the year
    std::sort(this->edges.begin(), this->edges.end(), [](const Edge* ed1, const Edge *ed2){
        return ed1->year < ed2->year;
    });

    int connectionYear = 0;

    // for each edge
    for(const Edge* ed : this->edges){
        int uId = ed->u;
        int vId = ed->v;
        int year = ed->year;

        int uParent = Find(uId, this->parent);
        int vParent = Find(vId, this->parent);

        // if the edge source and destination belongs to different groups, then group them togheter
        // check if the edge weight can be the solution
        if(uParent != vParent){
            Union(uParent, vParent, this->parent, this->rank);
            
            if(year > connectionYear) connectionYear = year; 
        }
    }

    return connectionYear;
}

long Graph::getConnectionCost(){
    // initialize Union-Find structure
    initTree();
    
    // sort edges by the cost
    std::sort(this->edges.begin(), this->edges.end(), [](const Edge* ed1, const Edge *ed2){
        return ed1->cost < ed2->cost;
    });

    long connectionCost = 0;

     // for each edge
    for(const Edge* ed : this->edges){
        int uId = ed->u;
        int vId = ed->v;
        int cost = ed->cost;

        int uParent = Find(uId, this->parent);
        int vParent = Find(vId, this->parent);

        // if the edge source and destination belongs to different groups, then group them togheter
        // sum the edge weight to the solution
        if(uParent != vParent){
            Union(uParent, vParent, this->parent, this->rank);
            
            connectionCost += cost;
        }
    }

    return connectionCost;
}