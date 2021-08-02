//
// Created by ZhouP on 4/15/2019.
//

#ifndef CPPSANDBOX_BURSTBUBBLE_H
#define CPPSANDBOX_BURSTBUBBLE_H

#include "../include/datastructure.h"


//1···················1    (len = 7)
//|     |
//left  right
//
//1···················1
//|     |
//left  right
//
//1···················1
//|     |
//left  right


//n^3
//
//int maxCoins(vector<int>& nums) {
//    int n = nums.size();
//    nums.insert(nums.begin(), 1);
//    nums.push_back(1);
//    vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), 0));
//    for (int len = 1; len <= n; ++len)
//        for (int left = 1; left <= n - len + 1; ++left) {
//            int right = left + len - 1;
//            for (int k = left; k <= right; ++k)
//                dp[left][right] = max(dp[left][right], nums[left-1]*nums[k]*nums[right+1] + dp[left][k-1] + dp[k+1][right]);
//        }
//    return dp[1][n];
//}

int burstbubble(Ints& values)
{

}

void test_burstbubble()
{
    Ints values = {3,1,5,8};

    printVector(values);
    std::cout << "max bubble burst score is " << burstbubble(values) << std::endl;
}

#endif //CPPSANDBOX_BURSTBUBBLE_H
