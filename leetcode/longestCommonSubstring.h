//
// Created by ZhouP on 4/16/2019.
//

#ifndef CPPSANDBOX_LONGESTCOMMONSUBSTRING_H
#define CPPSANDBOX_LONGESTCOMMONSUBSTRING_H

//The longest common suffix has following optimal substructure property
//        LCSuff(X, Y, m, n) = LCSuff(X, Y, m-1, n-1) + 1 if X[m-1] = Y[n-1]
//0  Otherwise (if X[m-1] != Y[n-1])
//
//The maximum length Longest Common Suffix is the longest common substring.
//LCSubStr(X, Y, m, n)  = Max(LCSuff(X, Y, i, j)) where 1 <= i <= m
//and 1 <= j <= n

// please note LCSubStr(X, Y, m, n) does NOT necessary mean the longest sub string length!!!
// Look at lcsubstr array below and you see LCSubStr(X, Y, m, n) == 0!!!
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
//0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,1,0,0,0,0,4,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,
//0,1,0,0,0,0,1,0,0,7,1,0,0,0,0,0,0,0,0,0,0,
//0,1,0,0,0,0,1,0,0,1,8,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
//0,1,0,0,0,0,1,0,0,2,1,0,0,0,0,0,0,0,0,0,0,
//0,1,0,0,0,0,1,0,0,1,3,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

int findLongestCommonSub(std::string s0, std::string s1)
{
    int m = s0.length();
    int n = s1.length();
    int lcsubstr[m][n];
    int result = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i==0 || j==0)
                lcsubstr[i][j] = 0;
            else if (s0[i]==s1[j])
            {
                lcsubstr[i][j] = lcsubstr[i-1][j-1] + 1;
                result = std::max(result, lcsubstr[i][j]);
            }
            else
                lcsubstr[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << lcsubstr[i][j] << "," ;
        }
        std::cout << std::endl;
    }

    return result;
}

void test_findLongestCommonSub()
{
    std::string X = "OldSite:GeeksforGeeks.org";
    std::string Y = "NewSite:GeeksQuiz.com";

    std::cout << "Length of Longest common sub string between " << X << " and " << Y << " is " << findLongestCommonSub (X, Y) << std::endl;
}

#endif //CPPSANDBOX_LONGESTCOMMONSUBSTRING_H
