//
// Created by ZhouP on 3/21/2019.
//

//TODO_
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

#ifndef CPPSANDBOX_DIJKSTRA_H
#define CPPSANDBOX_DIJKSTRA_H

#include "../include/datastructure.h"

#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d tt %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V];     // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist, V);
}

int findIndexofMinDistanceVertexVisited(const Ints& distance, const Bools& visited)
{
    // index of vertex that has minimum distance from visited (true)
    int min_dist(INT_MAX), min_index(-1);
    int count = distance.size();
    for (int i = 0; i < count; ++i) {
        if (!visited[i] && distance[i] <= min_dist)
        {
            min_dist = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

template<int VCOUNT>
void internal_test_dijkstra(int graph[VCOUNT][VCOUNT], int start)
{
    Ints distance(VCOUNT, INT_MAX);
    Bools visited(VCOUNT, false);

    distance[start] = 0;
    for (int i = 0; i < VCOUNT; ++i) {
        int min_index  = findIndexofMinDistanceVertexVisited(distance, visited);

        visited[min_index] = true;

        // update all the unvisited neighbors
        for (int j = 0; j < VCOUNT; ++j)
            if (!visited[j] && graph[min_index][j] && distance[min_index] != INT_MAX && (distance[min_index]+graph[min_index][j] < distance[j]))
                distance[j] = distance[min_index]+graph[min_index][j];
    }

    printVector<decltype(distance)::value_type>(distance);
}


// driver program to test above function
int test_dijkstra()
{
    /* Let us create the example graph discussed above */
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

//    int graph[V][V] = {{0, 2, 0, 6, 0},
//                       {2, 0, 3, 8, 5},
//                       {0, 3, 0, 0, 7},
//                       {6, 8, 0, 0, 9},
//                       {0, 5, 7, 9, 0}};

    dijkstra(graph, 0);

    internal_test_dijkstra<V>(graph, 0);

    int distance[V];
    std::for_each(std::begin(distance), std::end(distance), [](int & d) {d=-1;});
    std::for_each(std::begin(distance), std::end(distance), [](const int d) {printf("%d,", d);});
    printf("\n");

    return 0;
}

#endif //CPPSANDBOX_DIJKSTRA_H
