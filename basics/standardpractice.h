//
// Created by ZhouP on 3/15/2019.
//

#ifndef CPPSANDBOX_STANDARDPRACTICE_H
#define CPPSANDBOX_STANDARDPRACTICE_H

// this file is to practice standard template library functions

#include <algorithm>
#include "../include/datastructure.h"

void test_heap ()
{
    Ints heap { 3, 1, 4, 1, 5, 9 };

    printVector(heap);

    std::make_heap(heap.begin(), heap.end());

    printVector(heap);

    int num = 7;
    printf ("push in %d\n", num);
    heap.push_back(num);
    std::push_heap(heap.begin(), heap.end());
    printVector(heap);

    std::pop_heap(heap.begin(), heap.end());
    printf ("heap back is %d\n", heap.back());
    heap.pop_back();
    printVector(heap);
}

#endif //CPPSANDBOX_STANDARDPRACTICE_H
