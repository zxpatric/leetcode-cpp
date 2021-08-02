//
// Created by ZhouP on 3/22/2019.
//

#ifndef CPPSANDBOX_INSERTSORT_H
#define CPPSANDBOX_INSERTSORT_H

#include "../include/datastructure.h"
#include <algorithm>
#include <chrono>
#include <random>

//insertion sort: elements are inserted into the sorted section
// {9, 8, 7, 6, 5, 4, 3, 2, 1} -> {8, 9, 7, 6, 5, 4, 3, 2, 1} -> {7, 8, 9, 6, 5, 4, 3, 2, 1}  -> ....

void insertsort (Ints& values)
{
    // An insert sort using the stl::rotate. It is much faster than the individual swap implementation
    int num = values.size();
    for (int i = 0; i < num; ++i) {
        std::rotate (std::upper_bound(values.begin(), values.begin()+i, values[i]), values.begin()+i, values.begin()+i+1);
    }
//    for (int i = 1; i < num; ++i) {
//        int value = values[i];
//        int j = i-1;
//        for (; j >=0; --j) {
//            if(values[j]<value)
//            {
//                break;
//            }
//            else
//            {
//                values[j+1]=values[j];
//            }
//        }
//        values[j+1]=value;
//    }
}

//selection sort: elements are selected from unsorted section and appended to the sorted section
// {9, 8, 7, 6, 5, 4, 3, 2, 1} -> {8, 9, 7, 6, 5, 4, 3, 2, 1} -> {7, 8, 9, 6, 5, 4, 3, 2, 1}  -> ....

void selectionsort (Ints& values)
{
    // An insert sort using the stl
    int num = values.size();
    for (int i = 0; i < num; ++i) {
        int value = values[i];
        int index = -1;
        for (int j = i+1; j < num; ++j) {
            if (values[j]<value)
            {
                value = values[j];
                index = j;
            }
        }
        if (index>=0) {
            std::iter_swap(values.begin()+index, values.begin()+i);
        }
    }
}

//bubble sort the maximums are bubbled out of the unsorted section.
// {5, 2, 4, 7, 11, 8, 6} -> {2, 5, 4, 7, 11, 8, 6} -> {2, 4, 5, 7, 11, 8, 6} -> {2, 4, 5, 7, 8, 11, 6} -> {2, 4, 5, 7, 8, 6, 11} ->...
// {9, 8, 7, 6, 5, 4, 3, 2, 1}  -> ....{8, 7, 6, 9, 5, 4, 3, 2, 1}..... -> {8, 7, 6, 5, 4, 3, 2, 1, 9} -> ....

void bubblesort(Ints& values)
{
    int count = values.size();
    for (int i = 0; i < count-1; ++i) {
        for (int j = 0; j < count-1-i; ++j) {
            if (values[j]>values[j+1])
            {
                std::iter_swap(values.begin()+j, values.begin()+j+1);
            }
        }
    }
}

Ints generateRandomNumbers()
{
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist {1, 1052};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };

    std::vector<int> vec(1000);
    generate(begin(vec), end(vec), gen);

    return vec;
}

void test_insertbubblesort ()
{
//    Ints values = unsorted_ints;
//    Ints values = very_unsorted_ints;
    Ints values = generateRandomNumbers();
    printf("\nunsorted ");
    printVector<int> (values);
    Ints values2 = values;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    insertsort(values);     //3003ms
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
    selectionsort(values2);     //2502ms
//    bubblesort(values);     //40031ms  or so, takes longer than insertsort
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    printf("\nsorted in %d ms to ", duration);
    printVector<int> (values);
    printf("\n");

    auto another_duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t ).count();

    printf("\nsorted total %d ms and another %d\n", duration, another_duration);

}


#endif //CPPSANDBOX_INSERTSORT_H
