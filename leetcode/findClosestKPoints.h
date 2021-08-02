//
// Created by ZhouP on 5/30/2019.
//

#ifndef CPPSANDBOX_LEETCODE_FINDCLOSESTKPOINTS_H_
#define CPPSANDBOX_LEETCODE_FINDCLOSESTKPOINTS_H_

#include "../include/datastructure.h"

double squareDistance (const IntPair& p)
{
  return p.first*p.first + p.second*p.second;
}

struct lessDistance {
  bool operator() (const IntPair& p0, const IntPair& p1) const {return squareDistance(p0)>squareDistance(p1);}
};

IntPairs findClosestKPoints (const IntPairs& points, int K)
{
  IntPairs results;

  std::priority_queue<IntPair, IntPairs, lessDistance> points_lessFromOrigin_queue;

  int count = points.size();

  int i=0;
  for(; i<std::min(K, count); ++i)
  {
    points_lessFromOrigin_queue.push(points[i]);
  }

  while(K>0)
  {
    results.push_back(points_lessFromOrigin_queue.top());
    points_lessFromOrigin_queue.pop();
    --K;

    if (i<count)
    {
      points_lessFromOrigin_queue.push(points[i]);
      ++i;
    }
  }

  return results;
}


class Printor
{
 public:
  // This operator overloading enables calling
  // operator function () on objects of increment
  void operator () (const IntPair& p) const {
    std::cout << p.first << " & " << p.second << std::endl;
  }
};

void printing (const IntPair& p)
{
  printf ("%d | %d\n", p.first, p.second);
}

template<typename Func>
void findClosestKPoints (const IntPairs& points, int K, Func functor)
{
  std::priority_queue<IntPair, IntPairs, lessDistance> points_lessFromOrigin_queue;

  int count = points.size();

  int i=0;
  for(; i<std::min(K, count); ++i)
  {
    points_lessFromOrigin_queue.push(points[i]);
  }

  while(K>0)
  {
    functor(points_lessFromOrigin_queue.top());
    points_lessFromOrigin_queue.pop();
    --K;

    if (i<count)
    {
      points_lessFromOrigin_queue.push(points[i]);
      ++i;
    }
  }
}

// It is difficult to implement a yield in this case!!!

//    auto&& function = []() { int i = 0; return [=]() mutable { int arr[] = {1,2,4,8,16,16777216}; if ( i < 6 ) return arr[i++]; return 0; }; }();
//    for ( unsigned long i = 0; i != 10; ++i )
//        std::cout << "\t" << function() << "\t|";
//    std::cout << "\n";

void test_findClosestKPoints()
{
  IntPairs points = {{1, 2}, {3, 4}, {5, 6}};
  int K = 2;

//  IntPairs result = std::move(findClosestKPoints(points, K));
//  std::cout << "Closest " << K << " points to origin are :" << std::endl;
//  for (auto [x, y] : result)
//  {
//    std::cout << x << " , " << y << std::endl;
//  }

//  findClosestKPoints(points, K, Printor());
  findClosestKPoints(points, K, &printing);
}

#endif //CPPSANDBOX_LEETCODE_FINDCLOSESTKPOINTS_H_
