//
// Created by ZhouP on 5/9/2019.
//

#ifndef CPPSANDBOX_LEETCODE_COUNTANDSAY_H_
#define CPPSANDBOX_LEETCODE_COUNTANDSAY_H_

#include <string>

using namespace std;

string countAndSay(int n) {
  if (n <= 0) return "";
  string res = "1";
  while (--n) {
    string cur = "";
    for (int i = 0; i < res.size(); i++) {
      int count = 1;
      while ((i + 1 < res.size()) && (res[i] == res[i + 1])){
        count++;
        i++;
      }
      cur += to_string(count) + res[i];
    }
    res = cur;
  }
  return res;
}

void testCountAndSay()
{
  std::cout << countAndSay(11) << std::endl;
}

#endif //CPPSANDBOX_LEETCODE_COUNTANDSAY_H_
