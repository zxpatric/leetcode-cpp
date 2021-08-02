//
// Created by zxpat on 1/12/2020.
//

#ifndef CPPSANDBOX_MINIMUMSUM_H
#define CPPSANDBOX_MINIMUMSUM_H

#include <functional>
#include <math.h>
#include "../include/datastructure.h"

UInt find_minimum_sum(UInts& values, UInt times)
{
//    std::priority_queue<UInt, UInts> queue(std::less<UInt>(), values);

    if (values.size() == 0)
        return 0;

    for (UInt i = 0; i < times; ++i) {
        std::make_heap(unsorted_uints.begin(), unsorted_uints.end());
        unsorted_uints[0] = (UInt)std::ceil((double)unsorted_uints[0]/2.0f);
    }

    UInt sum(0);
    for (UInt val : values)
    {
        sum += val;
    }

    return sum;
}

void test_minimum_sum ()
{
    printVector(unsorted_uints);
    UInt times = 5;
    std::cout << "After " << times << " operations, the minimum sum is " << find_minimum_sum(unsorted_uints, times);
}

#endif //CPPSANDBOX_MINIMUMSUM_H
