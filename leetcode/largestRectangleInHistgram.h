//
// Created by ZhouP on 5/23/2019.
//

#ifndef CPPSANDBOX_LEETCODE_LARGESTRECTANGLEINHISTGRAM_H_
#define CPPSANDBOX_LEETCODE_LARGESTRECTANGLEINHISTGRAM_H_


#include "../include/datastructure.h"

int largestRectangleArea(const Ints& heights) {
  int largest(0);

  int size = heights.size();
  for (int i = 0; i < size; ++i)
  {
    int count(1);
    int height = heights[i];
    for (int j = i-1; j >= 0; --j) {
        if(heights[j] >= height)
          ++count;
        else
          break;
    }

    for (int k = i+1; k < size; ++k) {
      if(heights[k] >= height)
        ++count;
      else
        break;
    }

    int area = count * height;
    if (area > largest)
      largest = area;
  }

  return largest;
}

void test_largestRectangleArea()
{
  Ints heights = {2,1,5,6,2,3};

  std::cout << "The largest rectangle is of area " << largestRectangleArea (heights) << std::endl;
}

#endif //CPPSANDBOX_LEETCODE_LARGESTRECTANGLEINHISTGRAM_H_
