//
// Created by ZhouP on 4/17/2019.
//

#ifndef CPPSANDBOX_PERFECTSQUARE_H
#define CPPSANDBOX_PERFECTSQUARE_H

#include "../include/datastructure.h"

int numSquares(int n)
{
    if (n <= 0)
    {
        return 0;
    }

    // cntPerfectSquares[i] = the least number of perfect square numbers
    // which sum to i. Note that cntPerfectSquares[0] is 0.
    Ints cntPerfectSquares(n + 1, INT_MAX);
    cntPerfectSquares[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        // For each i, it must be the sum of some number (i - j*j) and
        // a perfect square number (j*j).
        for (int j = 1; j*j <= i; j++)
        {
            cntPerfectSquares[i] = std::min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
        }
    }

    printVector(cntPerfectSquares);

    return cntPerfectSquares.back();
}

void test_PerfectSquare()
{
    int n = 20;
    std::cout << numSquares (n) << std::endl;
}
#endif //CPPSANDBOX_PERFECTSQUARE_H
