//Given two strings text1 and text2, return the length of their longest common subsequence.

#include "../include/datastructure.h"

int findLongestCommon(std::string str0, std::string str1)
{
    int s0 = str0.size();
    int s1 = str1.size();

    std::vector<std::vector<int>> matrix (s0 + 1, std::vector<int>(s1 + 1));
    
    for(int i = 1; i < s0+1; i++)
    {
        /* code */
        
        for(int j = 1; j < s1+1; j++)
        {
            /* code */
            if (str0[i-1] == str1[j-1])
            {
                matrix[i][j] = matrix[i-1][j-1] + 1;
            }
            else
            {
                matrix[i][j] = std::max(matrix[i][j-1], matrix[i-1][j]);
            }
        }
    }
    
    return matrix[s0][s1];
}

void test_findLongestCommon()
{
    std::string text1 = "abcde";
    std::string text2 = "ace";

    std::cout << text1 << " ^ " << text2 << " is " << findLongestCommon (text1, text2) << std::endl;
}
