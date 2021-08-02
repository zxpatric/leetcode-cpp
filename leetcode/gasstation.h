//
// Created by ZhouP on 3/23/2019.
//

#ifndef CPPSANDBOX_GASSTATION_H
#define CPPSANDBOX_GASSTATION_H

#include "../include/datastructure.h"

int find_first_gasstation (const Ints& gas, const Ints& cost)
{
    int count = gas.size();
//    assert(cost.size()==count);

    int residual = 0;
    int index = 0;
    for(int i=0;i<count;++i)
    {
        int res = gas[i]-cost[i];
        residual += res;

        if (residual <= 0)
        {
            index = i+1;
            residual = 0;
        }
    }
    if (index==count)
    {
        index = 0;
    }

    return index;
}

void test_gasstation()
{
//    Ints gas = {1, 8, 2, 4};
//    Ints cost = {2, 4, 4, 5};

//    Ints gas = {1, 2, 2, 4};
//    Ints cost = {1, 2, 2, 4};

    Ints gas = {1, 3, 9, 2, 4};
    Ints cost = {2, 4, 4, 4, 5};

    int index = find_first_gasstation(gas, cost);
    printf("To go a circle, car needs to start from gas station %d", index);
}

#endif //CPPSANDBOX_GASSTATION_H
