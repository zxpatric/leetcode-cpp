//
// Created by ZhouP on 4/2/2019.
//

#ifndef CPPSANDBOX_JUMPGAME_H
#define CPPSANDBOX_JUMPGAME_H

#include "../include/datastructure.h"

bool recursive_check_jump (const Ints& jumps, Ints& canjumps, int index)
{
    int count = jumps.size();
    if (canjumps[index]>0)
        return true;
    else if (!canjumps[index])
        return false;
    else
    {
        int jump = jumps[index];
        if (jump <= 0)
        {
            canjumps[index]=0;
        }
        else
        {
            //
            int max_jump = index+ jump;
            if (max_jump >= count)
            {
                canjumps[index]=1;
                return true;
            }
            else
            {
                for (int j = index+1; j <= max_jump; ++j)
                {
                    if (recursive_check_jump(jumps, canjumps, j))
                    {
                        canjumps[j]=1;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool check_jump (const Ints& jumps)
{
    int count = jumps.size();
    Ints canjumps(count, -1);

    return recursive_check_jump (jumps, canjumps, 0);
}

bool check_jump_easy (const Ints& jumps)
{
    int count = jumps.size();
    int maxjump = 0;
    for (int i = 0; i < count; ++i) {
        maxjump = std::max (maxjump-1, jumps[i]);
        if (maxjump <= 0)
            return false;
    }

    return true;
}

void test_jump()
{
    Ints values = {2, 3, 1, 1, 4};
//    Ints values = {3, 2, 1, 0, 4};
    printVector(values);
    std::cout << "It is " << std::boolalpha << check_jump_easy(values) << " to be able to jump to the end" << std::endl;
//    printf("It is %s to jump to the end\n", )
}

#endif //CPPSANDBOX_JUMPGAME_H
