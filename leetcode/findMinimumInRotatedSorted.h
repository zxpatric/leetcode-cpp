//
// Created by ZhouP on 3/11/2019.
//

#ifndef CPPSANDBOX_FINDMINIMUMINROTATEDSORTED_H
#define CPPSANDBOX_FINDMINIMUMINROTATEDSORTED_H

#include "../include/datastructure.h"

int internal_findInRotatedSorted (const Ints& vals, int start, int end, const int val)
{
    if (start > end)
        return -1;

    int middle = (start + end)/2;

    int start_value = vals[start];
    int middle_value = vals[middle];
    int end_value = vals[end];

    if (start_value == val)
        return start;
    else
        ++start;

    if (middle_value == val)
        return middle;

    if (end_value == val)
        return end;
    else
        --end;

    if (start_value<=middle_value)
    {
        if (val>start_value && val<middle_value)
            return internal_findInRotatedSorted (vals, start, middle-1, val);
        else //if (val>middle_value)
            return internal_findInRotatedSorted(vals, middle+1, end, val);
    }
    else
    {
        if (val>middle_value && val<end_value)
            return internal_findInRotatedSorted(vals, middle+1, end, val);
        else
            return internal_findInRotatedSorted (vals, start, middle-1, val);
    }
}

int findInRotatedSorted (const Ints& vals, const int val)
{
     return internal_findInRotatedSorted (vals, 0, vals.size()-1, val);
}

void test_findInRotatedSorted()
{
    int val = 4;
    Ints values = {4, 4, 5, 6, 7, 7, 8, 8, 9, 0, 0, 2, 3, 3, 3};
    printVector(values);
    printf ("%d is at index %d", val, findInRotatedSorted(values, val));
};

#endif //CPPSANDBOX_FINDMINIMUMINROTATEDSORTED_H
