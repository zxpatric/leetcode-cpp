//
// Created by ZhouP on 2/14/2019.
//

#ifndef UNTITLED_FIRSTMISSINGPOSITIVE_H
#define UNTITLED_FIRSTMISSINGPOSITIVE_H

#include <vector>

class Solution {
public:
    static int firstMissingPositive(std::vector<int>& nums) {
        int num = (int)nums.size();
        if (num==0)
            return 1;

        ++num;
        std::vector<bool> flags(num);

        flags[0] = true;
        for (const int& i : nums)
        {
            if (i > 0 && i<num)
                flags[i] = true;
        }

        int j = 0;
        for (; j < num; ++j) {
            if(!flags[j])
                return j;
        }

        return j;
    }
};

#endif //UNTITLED_FIRSTMISSINGPOSITIVE_H


//    std::vector<int> input = {1};
//    std::cout << Solution::firstMissingPositive(input) << std::endl;