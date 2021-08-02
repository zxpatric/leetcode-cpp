//
// Created by ZhouP on 3/29/2019.
//

#ifndef CPPSANDBOX_LONGESTINCREASINGPATH_H
#define CPPSANDBOX_LONGESTINCREASINGPATH_H

// Given an integer matrix, find the length of the longest increasing path.

// int matrix[m][n]

// the path can go backforward, forward, upforward and downward

#include <map>
#include <set>

//<= is different from <


typedef std::map<int, int> PosMax;
typedef std::set<int> PosVisited;

std::vector<int> leftright = {-1,  0, 1, 0};
std::vector<int> updown    = {0 , -1, 0, 1};

template <int m, int n>
dfs_findTheLongestIncreasingPath (int matrix[m][n], int index, int length, PosVisited& visited, PosMax& mPosMax)
{
    // check out self
    auto iter = mPosMax.find(index);
    if(iter!=mPosMax.end())
    {
        return iter->second;
    }
    else
    {
        // check out neighbors
        int count = leftright.size();
        int r = index / n;
        int c = index % n;
        int value = matrix[r][c];
        int max_length = length;
        for (int i = 0; i<count; ++i)
        {
            int new_r = r + leftright[i];
            int new_c = c + updown[i];
            int new_index = new_r*n+new_c;
            if (new_r>=0&&new_r<m&&new_c>=0&&new_c<n&&value<matrix[new_r][new_c]&&visited.find(new_index)==visited.end())
            {
                visited.emplace(index);
                int mLength = 0;
                auto iter = mPosMax.find(new_index);
                if(iter != mPosMax.end())
                {
                    mLength = iter->second + length;
                }
                else
                {
                    mLength = dfs_findTheLongestIncreasingPath<m,n> (matrix, new_index, length+1, visited, mPosMax);
                }
                visited.erase(index);

                if (max_length < mLength)
                {
                    max_length = mLength;
                }
            }
        }
        mPosMax.emplace (index, max_length);
        return max_length;
    }
}

template <int m, int n>
int internal_findTheLongestIncreasingPath (int matrix[m][n], int index, PosMax& mPosMax)
{
    PosVisited visited;
    int length = 1;
    return dfs_findTheLongestIncreasingPath<m,n> (matrix, index, length, visited, mPosMax);
}

template<int m, int n>
int findTheLongestIncreasingPath(int matrix[m][n])
{
    // O(m*n+m*n) = O(m*n)
    int maxLength = 0;
    PosMax mPosMax;
    for (int i = 0; i<m; ++i)
    {
        for (int j = 0; j<n; ++j)
        {
            // start to find the maximum length of the longest increasing path starting i,j
            int index = i*n + j;
            int length = internal_findTheLongestIncreasingPath<m,n>(matrix, index, mPosMax);
//            mPosMax.emplace (index, maxLength);
            if (maxLength < length)
            {
                maxLength = length;
            }
        }
    }

    return maxLength;
}

void test_findTheLongestIncreasingPath ()
{
    int nums[3][3] = {
            {9,9,4},
            {6,6,8},
            {2,1,1}
    };

    int maxLength = findTheLongestIncreasingPath<3,3>(nums);
    std::cout << "Longest increasing path is " << maxLength << std::endl;
}

#endif //CPPSANDBOX_LONGESTINCREASINGPATH_H
