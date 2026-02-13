# Graph Toolkit in C++

A modular graph processing toolkit implemented in C++.

## Features

- BFS (Breadth First Search)
- DFS (Depth First Search)
- Shortest Path using BFS (Path Reconstruction)
- Dijkstra’s Algorithm
- Prim’s Minimum Spanning Tree
- Kruskal’s Minimum Spanning Tree
- Interactive CLI Menu
- Loop-based execution (run multiple algorithms without restart)

## Project Structure

GraphVisualiser/
│
├── include/core/Graph.h
├── src/core/Graph.cpp
├── main.cpp
├── README.md

## How to Compile

g++ -std=c++17 -Iinclude main.cpp src/core/Graph.cpp -o graph

## How to Run

./graph

## Example Input

Enter number of vertices: 5  
Enter number of edges: 6  
Enter edges (u v weight):

0 1 4  
0 2 1  
1 2 2  
1 3 5  
2 3 8  
3 4 3  

## Concepts Used

- Object-Oriented Programming
- Graph Data Structures
- STL (vector, queue, priority_queue, etc.)
- Algorithm Design
- CLI Application Design

## Author

Tushar Yadav
