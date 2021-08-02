//
// Created by ZhouP on 4/23/2019.
//

#ifndef CPPSANDBOX_ISMATCHSTRING_H
#define CPPSANDBOX_ISMATCHSTRING_H

#include <string>

bool isMatch (std::string s0, std::string s1)
{
    int index0 = s0.length()-1;
    int index1 = s1.length()-1;

    do
    {
        int count0(0);
        while(index0>=0)
        {
            if(s0[index0]=='_')
            {
                --index0;
                ++count0;
            }
            else
            {
                if (count0>0)
                {
                    --index0;
                    --count0;
                }
                else
                    break;
            }
        }

        int count1(0);
        while(index1>=0)
        {
            if(s1[index1]=='_')
            {
                --index1;
                ++count1;
            }
            else
            {
                if (count1>0)
                {
                    --index1;
                    --count1;
                }
                else
                    break;
            }
        }

        if(index0 >=0 && index1>=0)
        {
            if (s0[index0]!=s1[index1])
                break;
            else
            {
                --index0;
                --index1;
            }
        }
    }
    while(index0>=0 && index1>=0);

    return index0<0 && index1<0;
}

void test_isStringMatch()
{
    std::string s0 = "abcdf_e___";
    std::string s1 = "";

    std::cout << s0 << " matches " << s1 << " is " << std::boolalpha << isMatch(s0, s1)<< std::endl;
}

#endif //CPPSANDBOX_ISMATCHSTRING_H
