#include "Graph.hpp"
#include <iostream>


int main(){
    // problem variables
    int n, m, d, nb, i, j;
    double x, y;

    std::cin >> n >> m;

    // Graph initialization
    Graph *g = new Graph(n, m);

    //read n vertices
    for(i = 0; i < n; i++){
        std::cin >> x >> y >> d;

        Point *p = new Point(i + 1, d, x, y);

        // read d neighbours of v_i
        for(j = 0; j < d; j++){
            std::cin >> nb;
            p->addNeighbor(nb);
        }
        // add to the graph adjacency list
        g->addPoint(p);
    }

    std::vector<std::vector<int>> faces = g->getFaces();
    delete g;

    // print the graph faces
    int facesSize = faces.size();
    std::cout << facesSize << "\n";
    
    for(i = 0; i < facesSize; i++){
        int faceSize = faces[i].size();
        std::cout << faceSize;

        for(j = 0; j < faceSize; j++){
            std::cout << " " << faces[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}