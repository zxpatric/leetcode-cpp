//
// Created by ZhouP on 4/6/2019.
//

#ifndef CPPSANDBOX_FINDSINGLEAPPEARANCE_H
#define CPPSANDBOX_FINDSINGLEAPPEARANCE_H

#include "../include/datastructure.h"

int findSingleAppearance(const Ints& values)
{
    int count = values.size();
    if (count%2==0)
        throw std::invalid_argument("invalid input of size " + std::to_string(count));
    else if (count == 1)
        return values.front();
    else
    {
        int single = values.front();
        for (int i = 1; i < count; ++i) {
            single ^= values[i];
        }
        return single;
    }
}

void test_findSingleAppearance()
{
    Ints values = {1, 1, 2, 2, 5, 5, 7, 10, 10};

    std::cout << " Among ";
    printVector(values);
    std::cout << " the non-duplicated number is " << findSingleAppearance(values) << std::endl;
}

#endif //CPPSANDBOX_FINDSINGLEAPPEARANCE_H
