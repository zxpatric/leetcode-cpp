//
// Created by ZhouP on 4/27/2019.
//

#ifndef CPPSANDBOX_LEETCODE_SMALLESTSUBARRAY_H_
#define CPPSANDBOX_LEETCODE_SMALLESTSUBARRAY_H_

#include "../include/datastructure.h"

int smallestSubarray(const Ints& values, const int x)
{
    int count = values.size();

    int minSize (INT_MAX);
    for (int i = 0; i < count; ++i)
    {
      int value (0);
      for (int j = i; j < count; ++j) {
        value += values[j];
        if(value > x)
          if (j < minSize)
            minSize = j;
      }
    }

    return minSize;
}

void test_smallestSubarray()
{
//  Ints values = {1, 4, 45, 6, 0, 19};
//  int x  =  51;

  Ints values = {1, 10, 5, 2, 7};
  int x  =  9;


  std::cout << "smallest array length is " << smallestSubarray(values, x) << std::endl;
}
#endif //CPPSANDBOX_LEETCODE_SMALLESTSUBARRAY_H_
