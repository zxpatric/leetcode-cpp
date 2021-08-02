//
// Created by ZhouP on 5/24/2019.
//

#ifndef CPPSANDBOX_LEETCODE_MAXRECTANGLE_H_
#define CPPSANDBOX_LEETCODE_MAXRECTANGLE_H_


//int maximalRectangle(vector<vector<char>>& matrix) {
//
//}

template<int m, int n>
int maximalRectangle (bool matrix[m][n])
{
  //scan from m-1, n -1 each row, each column all the way to 0, 0
  //a O(m*n) solution is possible.
}

void test_maximalRectangle()
{
  bool matrix[3][3] = {
      {true, false,false},
      {true, true, true},
      {false,true, true}
  };

//  {8, 7, 4},
//  {6, 5, 3},
//  {2, 1, 0}

  std::cout << "Maximal rectangle area is " << maximalRectangle<3,3>(matrix) << std::endl;
}


#endif //CPPSANDBOX_LEETCODE_MAXRECTANGLE_H_
