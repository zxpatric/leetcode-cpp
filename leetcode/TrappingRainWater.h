//
// Created by ZhouP on 4/11/2019.
//

#ifndef CPPSANDBOX_TRAPPINGRAINWATER_H
#define CPPSANDBOX_TRAPPINGRAINWATER_H

#include "../include/datastructure.h"

int trap(const Ints& height)
{
    if(height.size()<=1)
        return 0;
    int ans = 0;
    int size = height.size();
    Ints left_max(size), right_max(size);
    left_max[0] = height[0];
    for (int i = 1; i < size; i++) {
        left_max[i] = std::max(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = std::max(height[i], right_max[i + 1]);
    }
    for (int i = 1; i < size - 1; i++) {
        ans += std::min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
}

int get_TrappingRainWater(const Ints& values)
{
    return trap(values);
}

void test_TrappingRainWater()
{
    Ints values = {0,1,0,2,1,0,1,3,2,1,2,1};

    std::cout << "max rain water to trap is " << get_TrappingRainWater(values) << std::endl;
}

#endif //CPPSANDBOX_TRAPPINGRAINWATER_H
