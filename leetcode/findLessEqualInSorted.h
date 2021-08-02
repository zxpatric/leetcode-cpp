//
// Created by ZhouP on 4/1/2019.
//

#ifndef CPPSANDBOX_FINDLESSEQUALINSORTED_H
#define CPPSANDBOX_FINDLESSEQUALINSORTED_H

#include "../include/datastructure.h"

int recursive_findLessEqual(const Ints sorted_values, int start, int end, int toFind) {

    if (start >= end)
    {
//        int start = std::max(start,end);
        if (sorted_values[start] <= toFind)
        {
            return start;
        }
        else
        {
            return start-1;
        }
    }
    else
    {
        // recursive search is actually very expensive due to the call stack preparation
        // use the linear search if the range is small.
        if (end-start < 10)
        {
            auto iter = std::upper_bound(sorted_values.begin()+start, sorted_values.begin()+end+1, toFind);
            return std::distance(sorted_values.begin(), iter)-1;
        }

        int middle = (start+end)/2;
        if (sorted_values[middle] == toFind)
        {
            return middle;
        }
        else if(sorted_values[middle] < toFind)
        {
            return recursive_findLessEqual (sorted_values, middle+1, end, toFind);
        }
        else
        {
            return recursive_findLessEqual (sorted_values, start, middle-1, toFind);
        }
    }
}

int findLessEqual(const Ints sorted_values, int toFind)
{
    int count = sorted_values.size();
    if (count < 1)
    {
        return -1;
    }
    else
    {
        return recursive_findLessEqual (sorted_values, 0, count-1, toFind);
    }
}

void test_findLessEqualSorted()
{
    Ints values = sorted_ints;
    printVector(values);

    int toFind = 8; //5;
    int index = findLessEqual(values, toFind);

    if (index < 0)
    {
        printf("NO element is equal or less than %d in array\n", toFind);
    }
    else
    {
        printf("%dth element %d is equal or less than %d in array\n", index, values[index], toFind);
    }
}

int findLessEqualInRotated(const Ints sorted_values, int start, int end, int toFind)
{

    if (start < 0)
    {
        return -1;
    }
    else
    {
        if (start <= end)
        {
            return recursive_findLessEqual (sorted_values, start, end, toFind);
        }
        else
        {
            int last = sorted_values.back();
            int count = sorted_values.size();
            int index(0);
            if (toFind == last)
            {
                index = count - 1;
            }
            else if (toFind < last)
            {
                index = recursive_findLessEqual (sorted_values, start, count - 1, toFind);
                if (index < start)
                    index = -1;
            }
            else
            {
                index = recursive_findLessEqual (sorted_values, 0, end, toFind);
                if (index < 0)
                    index = count - 1;
            }

            return index;
        }
    }
}

void insertElementAndRemoveOutofRange (Ints& sorted_ints_rotated, int& start, int& end, int value, int range)
{
    if (start<0)
    {
        start = end = 0;
        sorted_ints_rotated[start] = (value);
        return;
    }

    int valueToFind = value-range;

    int index = findLessEqualInRotated (sorted_ints_rotated, start, end, valueToFind);
    if (index < 0)
    {
        sorted_ints_rotated[start] = value;
        end = start;
    }
    else
    {
        start = index;
        int count = sorted_ints_rotated.size() -1;
        if (end==count-1) {
            end = 0;
        }
        else
        {
            ++end;
        }
        sorted_ints_rotated[end]=value;
    }
}

void test_findLessEqualInRotated()
{
    Ints values = sorted_ints_rotated;
    printVector(values);

    int start = 3;
    int end = 2;

    int new_start(start), new_end(end);
    insertElementAndRemoveOutofRange (values, new_start, new_end, 15, 10);
    printVector(values);
    printf ("previous start %d end %d and now start %d end %d\n", start, end, new_start, new_end);

    int toFind = 0;
    int index = findLessEqualInRotated(values, new_start, new_end, toFind);

    if (index < 0)
    {
        printf("NO element is equal or less than %d in array\n", toFind);
    }
    else
    {
        printf("%dth element %d is equal or less than %d in array\n", index, values[index], toFind);
    }
}

void test_findLessEqual() {
    return test_findLessEqualInRotated();
}
#endif //CPPSANDBOX_FINDLESSEQUALINSORTED_H
