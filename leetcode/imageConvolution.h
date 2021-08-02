//
// Created by ZhouP on 5/29/2019.
//

#ifndef CPPSANDBOX_LEETCODE_IMAGECONVOLUTION_H_
#define CPPSANDBOX_LEETCODE_IMAGECONVOLUTION_H_

template<int m, int n>
void imageConvolution(int matrix[m][n])
{
//  for (int i = 0; i < m; ++i) {
//    for (int j = 0; j < n; ++j) {
//      // matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1]
//
//      if (i==0&&j==0)
//      {
//        // nothing
//      }
//      else if (i==0)
//      {
//        matrix[i][j] +=  matrix[i][j-1];
//      }
//      else if (j==0)
//      {
//        matrix[i][j] += matrix[i-1][j];
//      }
//      else
//      {
//        matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1];
//      }
//    }
//  }


  for (int k = 1; k < m; ++k) {
    matrix[k][0] += matrix[k-1][0];
  }

  for (int l = 1; l < n; ++l) {
    matrix[0][l] +=  matrix[0][l-1];
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
        matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1];
    }
  }
}

void test_imageConvolution()
{
  int matrix[3][3] = {
    {8, 7, 4},
    {6, 5, 3},
    {2, 1, 0}
  };

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout<< matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  imageConvolution<3,3> (matrix);

//  8 15 19
//  14 26 33
//  16 29 36

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout<< matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif //CPPSANDBOX_LEETCODE_IMAGECONVOLUTION_H_
