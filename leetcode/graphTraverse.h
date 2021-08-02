//
// Created by ZhouP on 3/13/2019.
//

#ifndef CPPSANDBOX_GRAPHTRAVERSE_H
#define CPPSANDBOX_GRAPHTRAVERSE_H

#include<iostream>
#include <list>

#include "../include/datastructure.h"

class Graph
{
    int m_V;    // No. of vertices

    // Pointer to an array containing adjacency
    // lists
    std::vector<std::list<int>> adjs;
public:
    Graph(int V):m_V(V)  // Constructor
    {
        adjs.resize(V);
    }

    // function to add an edge to graph
    void addEdge(int v, int w)
    {
        adjs[v].push_back(w);
    }

    // prints BFS traversal from a given source s
    void BFS(int s)
    {
        Bools visited;
        visited.resize(m_V);
        for(int i = 0; i < m_V; i++)
            visited[i] = false;

        std::queue<int> queue;
        visited[s] = true;
        queue.push(s);

        while (!queue.empty())
        {
            s = queue.front();
            printf("%d, ", s);
            queue.pop();

            for (auto i = adjs[s].begin(); i != adjs[s].end(); ++i)
            {
                if (!visited[*i])
                {
                    queue.push(*i);
                    visited[*i] = true;
                }
            }
        }
    }

    void DFSUtil(int v, Bools& visited)
    {
        // Mark the current node as visited and
        // print it
        visited[v] = true;
        printf("%d, ", v);

        // Recur for all the vertices adjacent
        // to this vertex
        for (auto i = adjs[v].begin(); i != adjs[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited);
    }

    void DFS(int i)
    {
        Bools visited;
        visited.resize(m_V);
        for(int i = 0; i < m_V; i++)
            visited[i] = false;

        DFSUtil(i, visited);
    }
};

void test_printGraphBFS ()
{
//    Graph g(4);
//    g.addEdge(0, 1);
//    g.addEdge(0, 2);
//    g.addEdge(1, 2);
//    g.addEdge(2, 0);
//    g.addEdge(2, 3);
//    g.addEdge(3, 3);
//    g.BFS(2);

    Graph g(7);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    // 1 - 2  -  4
    // |   |  /  |
    // 3 - 5  -  6

    printf("\nGraph BFS \t"); g.BFS(1);     // 1 2 3 4 5 6
    printf("\nGraph DFS \t"); g.DFS(1);     // 1 2 4 5 6 3
}

#endif //CPPSANDBOX_GRAPHTRAVERSE_H
