//
// Created by zxpat on 1/12/2020.
//

#ifndef CPPSANDBOX_REORDERZEROSINARRAY_H
#define CPPSANDBOX_REORDERZEROSINARRAY_H

#include "../include/datastructure.h"

UInts reorder_array_move_zeros1(const UInts& values)
{
    UInts new_values = values;
    int zero_index = 0;
    int non_zero_index = 0;
    int size = new_values.size();
    while (zero_index < size && non_zero_index < size)
    {
        while (new_values[zero_index]!=0 && zero_index < size)
        {
            ++zero_index;
        }

        if(non_zero_index<=zero_index)
            non_zero_index = zero_index + 1;

        while (new_values[non_zero_index]==0 && non_zero_index < size)
        {
            ++non_zero_index;
        }

        //swap the value
        new_values[zero_index] = new_values[non_zero_index];
        new_values[non_zero_index] = 0;

        ++zero_index;
        ++non_zero_index;
    }

    return new_values;
}

void test_reorder_array()
{
    UInts values = {1, 0, 0, 4, 0, 0, 3, 0};
    printVector(values);
    printVector(std::move(reorder_array_move_zeros1(values)));
}

#endif //CPPSANDBOX_REORDERZEROSINARRAY_H
