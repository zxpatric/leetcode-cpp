//
// Created by ZhouP on 4/8/2019.
//

#ifndef CPPSANDBOX_ISINCREASINGSEQUENCEEXIST_H
#define CPPSANDBOX_ISINCREASINGSEQUENCEEXIST_H

#include "../include/datastructure.h"

bool foundExistingIncreasingSequence (const Ints& values, int index, Ints& indexedValues)
{
    int value = values[index];
    int i = 0;
    int count = indexedValues.size();
    for (; i < count; ++i) {
        if (i==count-1)
        {
            if (value < indexedValues[i])
            {
                indexedValues[i] = value;
                return true;
            }
            return false;
        }
        else
        {
            if (value < indexedValues[i])
            {
                indexedValues[i] = value;
                break;
            }
        }
    }

    return false;
}

bool isExistingIncreasingSequence(const Ints& values, unsigned int n)
{
    Ints indexedValues(n, INT_MAX);

    int count = values.size();
    for (int i = 0; i < count; ++i) {
        if (foundExistingIncreasingSequence(values, i, indexedValues))
        {
            printVector(indexedValues);
            return true;
        }
    }
    printVector(indexedValues);
    return false;
}

void test_existingIncreasingSequence()
{
    Ints values = {1, 5, 2, 4, 3, 8};
//    Ints values = {1, 5, 4, 3, 2};
    int number = 4;

    printVector(values);
    std::cout << " has " << number << " number of values are increasing is " << std::boolalpha << isExistingIncreasingSequence(values, number) << std::endl;
}

#endif //CPPSANDBOX_ISINCREASINGSEQUENCEEXIST_H
