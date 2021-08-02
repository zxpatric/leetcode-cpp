//
// Created by ZhouP on 3/27/2019.
//

#ifndef CPPSANDBOX_MAXLENGTHSNAKE_H
#define CPPSANDBOX_MAXLENGTHSNAKE_H


#include <list>

#define M 4
#define N 4

using namespace std;

struct Point
{
    int x, y;
};

// Function to find maximum length Snake sequence path
// (i, j) corresponds to tail of the snake
list<Point> findPath(int grid[M][N], int mat[M][N], int i, int j)
{
    list<Point> path;

    Point pt = {i, j};
    path.push_front(pt);

    while (grid[i][j] != 0)
    {
        if (i > 0 &&
            grid[i][j] - 1 == grid[i - 1][j])
        {
            pt = {i - 1, j};
            path.push_front(pt);
            i--;
        }
        else if (j > 0 &&
                 grid[i][j] - 1 == grid[i][j - 1])
        {
            pt = {i, j - 1};
            path.push_front(pt);
            j--;
        }
    }

    return path;
}

// Function to find maximum length Snake sequence
void findSnakeSequence_rightdown(int mat[M][N])
{
    // table to store results of subproblems
    int lookup[M][N];

    // initialize by 0
    memset(lookup, 0, sizeof lookup);

    // stores maximum length of Snake sequence
    int max_len = 0;

    // store cordinates to snake's tail
    int max_row = 0;
    int max_col = 0;

    // fill the table in bottom-up fashion
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // do except for (0, 0) cell
            if (i || j)
            {
                // look above
                if (i > 0 &&
                    abs(mat[i - 1][j] - mat[i][j]) == 1)
                {
                    lookup[i][j] = max(lookup[i][j],
                                       lookup[i - 1][j] + 1);

                    if (max_len < lookup[i][j])
                    {
                        max_len = lookup[i][j];
                        max_row = i, max_col = j;
                    }
                }

                // look left
                if (j > 0 &&
                    abs(mat[i][j - 1] - mat[i][j]) == 1)
                {
                    lookup[i][j] = max(lookup[i][j],
                                       lookup[i][j - 1] + 1);
                    if (max_len < lookup[i][j])
                    {
                        max_len = lookup[i][j];
                        max_row = i, max_col = j;
                    }
                }
            }
        }
    }

    cout << "Maximum length of Snake sequence is: "
         << max_len << endl;

    // find maximum length Snake sequence path
    list<Point> path = findPath(lookup, mat, max_row,
                                max_col);

    cout << "Snake sequence is:";
    for (auto it = path.begin(); it != path.end(); it++)
        cout << endl << mat[it->x][it->y] << " ("
             << it->x << ", " << it->y << ")" ;
}



int findSnakeSequence(int mat[M][N]) {
//
    int max_value=0;
    int max_r = 0;
    int max_c = 0;
    int max[M][N];
    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < N; ++c) {
            max[r][c]=0;
            if (r || c)
            {
                int value = mat[r][c];

                int last_c = c-1;
                int last_r = r-1;

                if (last_c>=0&&abs(value-mat[r][last_c])==1)
                {
                    max[r][c]=std::max(max[r][c],max[r][last_c]+1);
                }
                if (last_r>=0&&abs(value-mat[last_r][c])==1)
                {
                    max[r][c]=std::max(max[r][c],max[last_r][c]+1);
                }
            }
            if(max_value < max[r][c])
            {
                max_value = max[r][c];
                max_r = r;
                max_c = c;
            }
        }
    }

    printf("Max length snake of %d ends at (%d, %d)", max_value, max_r, max_c);
}


// brutal force search!!!

#include <unordered_set>
typedef std::unordered_set<int> SetInts;

std::vector<int> updown = {0,-1,0,1};
std::vector<int> leftright = {-1,0,1,0};


int recursiveCall(int mat[M][N], int r, int c, SetInts& visited, SetInts& visited_this_time, int length)
{
    int max_length = ++length;
    int value = mat[r][c];
    for (int i = 0; i < 4; ++i) {
        int new_r = r+updown[i];
        int new_c = c+leftright[i];
        int new_index = new_r*N+new_c;

        if (visited_this_time.find(new_index)==visited_this_time.end() &&
            new_r>=0&&new_r<M&&new_c>=0&&new_c<N&&abs(value-mat[new_r][new_c])==1)
        {
            visited.emplace(new_index);
            visited_this_time.emplace(new_index);
            max_length=std::max(max_length, recursiveCall(mat, new_r, new_c, visited, visited_this_time, length));
            visited_this_time.erase(new_index);
        }
    }
    return max_length;
}

int internal_findSnakeSequence_AllDirection (int mat[M][N], int r, int c, SetInts& visited)
{
    SetInts visited_this_time;
    int value = mat[r][c];
//    int length = 1;
//    int max_length = 0;
//    for (int i = 0; i < 4; ++i) {
//        int new_r = r+updown[i];
//        int new_c = r+leftright[i];
//
//        if (new_r>=0&&new_r<M&&new_c>=0&&new_c<N)
//        {
//            max_length=std::max(max_length, recursiveCall(mat, new_r, new_c, visited, visited_this_time, length);
//        }
//    }
    return recursiveCall (mat, r, c, visited, visited_this_time, 0);
}

int findSnakeSequence_AllDirection(int mat[M][N]) {
//
    SetInts visited;
    int max_value =0;
    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < N; ++c) {
            int index = r*N+c;
            if (visited.find(index)==visited.end())
            {
                visited.emplace(index);
                max_value = std::max(max_value, internal_findSnakeSequence_AllDirection (mat, r, c, visited));
            }
        }
    }

    printf("Max length snake of %d", max_value);
}

void test_maxLengthSnake()
{
    int mat[M][N] =
    {
        {9, 6, 5, 2},
        {8, 7, 6, 5},
        {7, 3, 1, 6},
        {1, 1, 1, 7},
    };

//    findSnakeSequence_rightdown(mat);
//    findSnakeSequence(mat);
    findSnakeSequence_AllDirection(mat);
}

#endif //CPPSANDBOX_MAXLENGTHSNAKE_H
