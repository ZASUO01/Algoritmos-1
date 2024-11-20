#include <iostream>
#include <Graph.hpp>

int main(){
    int N, M, u, v, a, l , c;

    std::cin >> N >> M;
    
    Graph * g = new Graph(N, M);

    // reading edges information
    for(int i = 0; i < M; i++){
        std::cin >> u >> v >> a >> l >> c;

        g->addEdge(u, v, a, l, c);
    }

    // minimum distances from a starter vertex to all the others. start = 1
    std::vector<long> minDistances = g->getMinDistances(1);
    // minimum year which that distances can be achieved
    int minDistancesYear = g->getMinDistancesYear();
    // the first year in wich the graph is full connected
    int connectionYear = g->getConnectionYear();
    // the minimum cost to connected the graph
    long connectionCost = g->getConnectionCost();
    
    
    for(int i = 1; i <= N; i++){
        std::cout << minDistances[i] << "\n";
    }

    std::cout << minDistancesYear << "\n";
    std::cout << connectionYear << "\n";
    std::cout << connectionCost << "\n";

    delete g;

    return 0;
}