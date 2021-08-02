//
// Created by ZhouP on 5/11/2019.
//

#ifndef CPPSANDBOX_LEETCODE_FINDMAXISLAND_H_
#define CPPSANDBOX_LEETCODE_FINDMAXISLAND_H_

std::vector<int> leftright = {-1,  0, 1, 0};
std::vector<int> updown    = {0 , -1, 0, 1};

template <int m, int n>
void findMaxReaInslandFromHere(const bool values[m][n], int i, int j, bool visited[m][n], int& area)
{
    if (!values[i][j] || visited[i][j])
      return;

    visited[i][j] = true;
    ++area;

    int new_r, new_c;
  for (int k = 0; k < 4; ++k) {
    new_r = i + updown[k];
    new_c = j + leftright[k];

    if (new_r>=0&&new_r<m&&new_c>=0&&new_c<n)
      findMaxReaInslandFromHere<m,n> (values, new_r, new_c, visited, area);
  }
}

template <int m, int n>
int findMaxAreaInsland (const bool values[m][n])
{
  bool visited[m][n];
  int max_area(-1);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int area(0);
      findMaxReaInslandFromHere<m,n>(values, i, j, visited, area);
      max_area = std::max(max_area, area);
    }
  }
  return max_area;
}


void test_findMaxIsland()
{
  bool values[3][3] = {
      {true,false,true},
      {true,false,true},
      {false,false,true}
  };

  std::cout << findMaxAreaInsland<3,3> ( values ) << std::endl;
}

#endif //CPPSANDBOX_LEETCODE_FINDMAXISLAND_H_
