#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int,int>>> adj;
    void dfsUtil(int node, std::vector<bool>& visited);
    std::vector<std::tuple<int,int,int>> edges; 
// (weight, u, v)


public:
    Graph(int V);

    void addEdge(int u, int v, int w = 1, bool undirected = true);
    void display();
    int getVertices();
    void bfs(int start);
    void dfs(int start);
    void dijkstra(int start);
    void kruskalMST();
    void primMST();
    void shortestPath(int start, int end);


    vector<vector<pair<int,int>>> getAdjList();
};

#endif
