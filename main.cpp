#include <iostream>
#include "core/Graph.h"

using namespace std;

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v weight):\n";

    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int choice;
    int start, end;

    while(true) {

        cout << "\n===== GRAPH MENU =====\n";
        cout << "1. BFS\n";
        cout << "2. DFS\n";
        cout << "3. Shortest Path (BFS Path Reconstruction)\n";
        cout << "4. Dijkstra\n";
        cout << "5. Prim's MST\n";
        cout << "6. Kruskal's MST\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                cout << "Enter starting vertex: ";
                cin >> start;
                g.bfs(start);
                break;

            case 2:
                cout << "Enter starting vertex: ";
                cin >> start;
                g.dfs(start);
                break;

            case 3:
                cout << "Enter start and end vertex: ";
                cin >> start >> end;
                g.shortestPath(start, end);
                break;

            case 4:
                cout << "Enter starting vertex: ";
                cin >> start;
                g.dijkstra(start);
                break;

            case 5:
                g.primMST();
                break;

            case 6:
                g.kruskalMST();
                break;

            case 0:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
