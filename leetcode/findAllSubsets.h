//
// Created by ZhouP on 4/27/2019.
//

#ifndef CPPSANDBOX_LEETCODE_FINDALLSUBSETS_H_
#define CPPSANDBOX_LEETCODE_FINDALLSUBSETS_H_

#include "../include/datastructure.h"
#include <math.h>
#include <bitset>

typedef std::vector<Strings> Stringss;

Stringss findAllSubsets(const Strings& strs)
{
  int count = strs.size();
  int subset_count = pow(2, count);
  Stringss sss;
  sss.reserve(subset_count);
  for (int i = 0; i < subset_count; ++i) {
    std::bitset<32> bs(i);
    Strings subset;
    subset.reserve(count);
    for (int j = 0; j < bs.size(); ++j) {
      if (bs[j])
      {
        subset.push_back(strs[j]);
      }
    }
    sss.push_back(subset);
  }

  return sss;
}

void test_findAllSubsets ()
{
  Strings strs = {"a", "bc", "d"};

  Stringss strss = std::move (findAllSubsets(strs));

  std::for_each(strss.begin(), strss.end(), [](const Strings& ss){printVector(ss);});
}

#endif //CPPSANDBOX_LEETCODE_FINDALLSUBSETS_H_
