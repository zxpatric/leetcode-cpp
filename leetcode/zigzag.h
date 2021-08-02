//
// Created by ZhouP on 3/5/2019.
//

#ifndef CPPSANDBOX_ZIGZAG_H
#define CPPSANDBOX_ZIGZAG_H
#include <vector>

class Solution {
public:
    std::string convert(std::string s, int numRows) {
        if (numRows < 2)
        {
            return s;
        }

        int len = s.length();
        if (len < 2)
        {
            return s;
        }

        int half_mod_num = numRows-1;
        int mod_num = 2*numRows-2;
        std::vector<std::vector<int>> indexss;;
        indexss.resize(numRows);
        for (int i=0;i<len;++i)
        {
            int index = i%mod_num;
            if (index>half_mod_num) index = mod_num-index;
            indexss[index].push_back(i);
        }
        std::string result="";
        for (const std::vector<int>& indexs : indexss)
        {
            for (int index:indexs)
            {
                result+=s[index];
            }
        }

        return result;
    }
};
#endif //CPPSANDBOX_ZIGZAG_H
