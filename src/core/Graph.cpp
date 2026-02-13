#include "core/Graph.h"
#include <iostream>
#include <queue>
#include <vector>
#include<limits>
#include <algorithm>
#include <tuple>


using namespace std;

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w, bool undirected) {
    adj[u].push_back({v, w});
    if (undirected) {
        adj[v].push_back({u, w});
    }
    edges.push_back({w, u, v});  // store for Kruskal
}

void Graph::display() {
    cout << "Graph Adjacency List:\n";
    for(int i = 0; i < V; i++) {
        cout << i << " -> ";
        for(auto &p : adj[i]) {
            cout << "(" << p.first << ", w=" << p.second << ") ";
        }
        cout << endl;
    }
}

int Graph::getVertices() {
    return V;
}

vector<vector<pair<int,int>>> Graph::getAdjList() {
    return adj;
}
void Graph::bfs(int start) {
    std::vector<bool> visited(V, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    std::cout << "BFS Traversal: ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        std::cout << node << " ";

        for (auto neighbor : adj[node]) {
            int v = neighbor.first;   // since weighted pair
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    std::cout << std::endl;
}
void Graph::dfsUtil(int node, std::vector<bool>& visited) {
    visited[node] = true;
    std::cout << node << " ";

    for (auto neighbor : adj[node]) {
        int v = neighbor.first;
        if (!visited[v]) {
            dfsUtil(v, visited);
        }
    }
}

void Graph::dfs(int start) {
    std::vector<bool> visited(V, false);

    std::cout << "DFS Traversal: ";
    dfsUtil(start, visited);
    std::cout << std::endl;
}
void Graph::dijkstra(int start) {
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        for (auto neighbor : adj[node]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[node] + weight < dist[v]) {
                dist[v] = dist[node] + weight;
                parent[v] = node;   // 🔥 store parent
                pq.push({dist[v], v});
            }
        }
    }

    std::cout << "Dijkstra Shortest Paths from node " << start << ":\n";

    for (int i = 0; i < V; i++) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            std::cout << "Node " << i << " is unreachable\n";
            continue;
        }

        std::cout << "To " << i << " (Distance = " << dist[i] << "): Path = ";
        
        // Reconstruct path
        std::vector<int> path;
        for (int v = i; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        // Reverse path
        std::reverse(path.begin(), path.end());

        for (int node : path) {
            std::cout << node << " ";
        }

        std::cout << std::endl;
    }
}
// Disjoint Set (Union-Find)
class DisjointSet {
    std::vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY) {
            if(rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if(rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};
void Graph::kruskalMST() {
    std::sort(edges.begin(), edges.end());

    DisjointSet ds(V);

    int mstWeight = 0;

    std::cout << "Kruskal MST Edges:\n";

    for(auto edge : edges) {
        int w = std::get<0>(edge);
        int u = std::get<1>(edge);
        int v = std::get<2>(edge);

        if(ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            mstWeight += w;
            std::cout << u << " - " << v << " (weight " << w << ")\n";
        }
    }

    std::cout << "Total MST Weight: " << mstWeight << std::endl;
}
void Graph::primMST() {
    std::vector<int> key(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);
    std::vector<bool> inMST(V, false);

    // Min heap: (key, vertex)
    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    int totalWeight = 0;

    std::cout << "Prim MST Edges:\n";

    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i 
                      << " (weight " << key[i] << ")\n";
            totalWeight += key[i];
        }
    }

    std::cout << "Total MST Weight: " << totalWeight << std::endl;
}
void Graph::shortestPath(int start, int end) {

    std::vector<bool> visited(V, false);
    std::vector<int> parent(V, -1);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto neighbor : adj[node]) {
            int v = neighbor.first;

            if (!visited[v]) {
                visited[v] = true;
                parent[v] = node;
                q.push(v);
            }
        }
    }

    // If no path
    if (!visited[end]) {
        std::cout << "No path exists\n";
        return;
    }

    // Reconstruct path
    std::vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    std::reverse(path.begin(), path.end());

    std::cout << "Shortest Path: ";
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}
