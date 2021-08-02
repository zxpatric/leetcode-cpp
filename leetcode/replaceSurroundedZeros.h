//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_REPLACESURROUNDEDZEROS_H
#define CPPSANDBOX_REPLACESURROUNDEDZEROS_H

#include "../include/datastructure.h"

template<int m, int n>
void replaceSurroundedZeros (int graph[m][n])
{
    if (m<3 || m<3)
        return;

    /**
     * Use a queue to store index to do BFS
     * A 2d boolean array to remember whether a point is visited
     * A 2d int array to represent 4-connectivity
     *
     * Traverse through the board and BFS at where it's 'O' and not visited
     * Set surround as true at first
     * Create an integer list for points to change
     * Check points around to see whether there is an 'O' point within the board and not visited
     * If so, add it to queue, set visited true
     * If not, it's not surrounded
     */

//    bool visited[m][n];
//    std::queue<int> q;
//    int[][] dir = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
//
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++) {
//            if (graph[i][j] == 0 && !visited[i][j]) {
//                bool surround = true;
//                List<Integer> pointsToChange;
//                q.add(i * n + j); // add root
//                visited[i][j] = true; // set root visited
//                while (q.size() > 0) { // BFS
//                    int point = q.poll(); // get from queue
//                    pointsToChange.add(point);
//                    int x = point / n; // get coordinates
//                    int y = point % n;
//                    // try 4 direction
//                    for (int k = 0; k < dir.length; k++) {
//                        int nextX = x + dir[k][0];
//                        int nextY = y + dir[k][1];
//                        if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n) { // within board
//                            if (board[nextX][nextY] == 'O' && !visited[nextX][nextY]) // add to queue
//                                q.add(nextX * n + nextY);
//                            visited[nextX][nextY] = true; // set visited
//                        }
//                        else
//                            surround = false; // false if on the boundry
//                    }
//                }
//                if (surround) for (int p : pointsToChange) board[p / n][p % n] = 'X'; // set to 'X'
//            }
//        }
//    }

    int i,j;
    int connectivity[m][n];
    memset(connectivity, -1, sizeof(int)*m*n);
    // any connectivity value more than 4 means it is boundary!!! if you touched the boundary, you are safe!!!
    connectivity[0][0] = 9;
    connectivity[m-1][0] = 9;
    connectivity[0][n-1] = 9;
    connectivity[m-1][n-1] = 9;
    for(i=1;i<m-1;++i){connectivity[i][0] = 9;connectivity[i][n-1] = 9;}
    for(i=1;i<n-1;++i){connectivity[0][i] = 9;connectivity[m-1][i] = 9;}

    std::vector<int> offsets = {-1, +1, -n, +n};

    for (i = 1; i < m-1; i++) {
        for (j = 1; j < n-1; j++) {
            if (graph[i][j] == 0 && connectivity[i][j]<0) {
                std::queue<int> queue_pairs;
                std::unordered_map<int, bool> map_pairs;
                queue_pairs.push(i*n+j);

                bool allalive = false;

                while (!queue_pairs.empty())
                {
                    int key = queue_pairs.front();
                    queue_pairs.pop();
                    if (map_pairs.find(key)==map_pairs.end())
                    {
                        map_pairs.emplace(key, true);
                    }

                    // calculate its connectivity
                    int x = key/m;
                    int y = key%n;

                    int connectivity_count = 0;

                    for (const int offset:offsets)
                    {
                        int index = key + offset;
                        x = index/n;
                        y = index%n;
                        if (graph[x][y]==0){
                            ++connectivity_count;
                            if (connectivity[x][y]<0)
                                queue_pairs.push(index);
                            else
                                if (connectivity[x][y]>4)
                                    allalive = true;
                        }
                    }

                    x = key/n;
                    y = key%n;
                    connectivity[x][y]=connectivity_count;
                    // push all its 0 neighbors into queue_pairs
                }

                if (!allalive)
                {
                    std::for_each(map_pairs.begin(), map_pairs.end(), [&](auto pair){graph[pair.first/n][pair.first%n]=1;});
                }
            }
        }
    }

}

void test_replaceSurroundedZeros()
{
//    int graph[5][5] = {
//            {1, 1, 1, 1, 1},
//            {1, 1, 0, 0, 1},
//            {1, 0, 0, 0, 1},
//            {1, 1, 0, 1, 1},
//            {1, 1, 1, 0, 1},
//    };

    int graph[5][5] = {
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1},
            {1, 1, 0, 0, 1},
            {1, 1, 1, 0, 1},
    };


    printf("\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d, ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    replaceSurroundedZeros<5,5>(graph);

    printf("\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d, ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void test_pairAsKey()
{
    //can't use pair as hash key!!!
//    std::unordered_map<IntPair, bool> map_pairs;
//    map_pairs.emplace(std::make_pair(0,0), true);
//    map_pairs.emplace(std::make_pair(1,1), false);

    std::unordered_map<int, bool> map_pairs;
    map_pairs.emplace(0, true);
    map_pairs.emplace(1, false);
}



template<int m, int n>
void goCounting (int graph[m][n])
{
    if (m<3 || m<3)
        return;

    int i,j;
    int connectivity[m][n];
    memset(connectivity, -1, sizeof(int)*m*n);
    // any connectivity value more than 4 means it is boundary!!! if you touched the boundary, you are safe!!!
    connectivity[0][0] = 9;
    connectivity[m-1][0] = 9;
    connectivity[0][n-1] = 9;
    connectivity[m-1][n-1] = 9;
    for(i=1;i<m-1;++i){connectivity[i][0] = 9;connectivity[i][n-1] = 9;}
    for(i=1;i<n-1;++i){connectivity[0][i] = 9;connectivity[m-1][i] = 9;}

    std::vector<int> offsets = {-1, +1, -n, +n};

    for (i = 1; i < m-1; i++) {
        for (j = 1; j < n-1; j++) {
            if (graph[i][j] == 0 && connectivity[i][j]<0) {
                std::queue<int> queue_pairs;
                std::unordered_map<int, bool> map_pairs;
                queue_pairs.push(i*n+j);

                bool allalive = false;

                while (!queue_pairs.empty())
                {
                    int key = queue_pairs.front();
                    queue_pairs.pop();
                    if (map_pairs.find(key)==map_pairs.end())
                    {
                        map_pairs.emplace(key, true);
                    }

                    // calculate its connectivity
                    int x = key/m;
                    int y = key%n;

                    int connectivity_count = 0;

                    for (const int offset:offsets)
                    {
                        int index = key + offset;
                        x = index/n;
                        y = index%n;
                        if (graph[x][y]==0){
                            ++connectivity_count;
                            if (connectivity[x][y]<0)
                                queue_pairs.push(index);
                            else
                            if (connectivity[x][y]>4)
                                allalive = true;
                        }
                    }

                    x = key/n;
                    y = key%n;
                    connectivity[x][y]=connectivity_count;
                    // push all its 0 neighbors into queue_pairs
                }

                if (!allalive)
                {
                    std::for_each(map_pairs.begin(), map_pairs.end(), [&](auto pair){graph[pair.first/n][pair.first%n]=1;});
                }
            }
        }
    }

}

void test_goCounting()
{
    // go winning counting is quick difficult!!!
    int graph[8][8] = {
            {1, 2, 1, 2, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 1, 2, 1},
            {1, 0, 0, 0, 2, 1, 1, 1},
            {1, 0, 2, 0, 2, 0, 1, 1},
            {1, 0, 0, 0, 2, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 1, 1},
            {1, 0, 0, 0, 1, 1, 1, 1},
            {1, 0, 2, 0, 1, 2, 2, 0},
    };
}

#endif //CPPSANDBOX_REPLACESURROUNDEDZEROS_H
