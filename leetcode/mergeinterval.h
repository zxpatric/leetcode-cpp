//
// Created by ZhouP on 4/15/2019.
//

#ifndef CPPSANDBOX_MERGEINTERVAL_H
#define CPPSANDBOX_MERGEINTERVAL_H

#include "../include/datastructure.h"


bool mergeTwoInterval (IntPair& theOne, const IntPair& theOther)
{
    if (theOne.second < theOther.first || theOne.first > theOther.second)
        return false;
    else
    {
        theOne.first = std::min(theOne.first, theOther.first);
        theOne.second = std::max(theOne.second, theOther.second);
        return true;
    }
}

IntPairs mergeintervals(const IntPairs& pairs)
{
    IntPairs results;
    int count = pairs.size();
    Bools used;
    used.resize (count, false);
    IntPair theOne = pairs.front();
    used[0] = true;
    int start = 1;
    while (start<count)
    {
        bool updated = false;
//        bool merged = false;
        int i = start;
        for (; i < count; ++i)
        {
            if (used[i]==false)
            {
                const IntPair& ip = pairs[i];
                if (mergeTwoInterval(theOne, ip))
                {
                    used[i] = true;
//                    merged = true;
                }
                else
                {
                    if (!updated) {
                        start = i;
                        updated = true;
                    }
                    break;
                }
            }
        }

        if (!updated)
            start = i;

//        if (merged)
//        {
//            // do the whole thing again
//        }
        else
        {
            results.push_back(theOne);
            theOne = pairs[start++];
        }
    }
    results.push_back(theOne);

    return results;
}

void test_mergeinterval()
{
    IntPairs values =     {{1,3},{2,6},{8,10},{15,18}};
    IntPairs merged = mergeintervals (values);

    printVector(values);
    printVector(merged);
}

#endif //CPPSANDBOX_MERGEINTERVAL_H
