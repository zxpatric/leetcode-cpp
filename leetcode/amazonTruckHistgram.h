//
// Created by ZhouP on 5/23/2019.
//

#ifndef CPPSANDBOX_LEETCODE_AMAZONTRUCKHISTGRAM_H_
#define CPPSANDBOX_LEETCODE_AMAZONTRUCKHISTGRAM_H_

#include "../include/datastructure.h"

typedef std::tuple<int, int, float> StartEndSpeed;
typedef std::vector<StartEndSpeed> VecStartEndSpeeds;
typedef std::pair<int, float> TimeSpeed;
typedef std::vector<TimeSpeed> VecTimeSpeeds;

struct EarlierEnd {
  bool operator() (const TimeSpeed& x, const TimeSpeed& y) const {return x.first > y.first;}
};

VecTimeSpeeds getAmazonTruckHistgram (const VecStartEndSpeeds& trucks)
{
  VecTimeSpeeds time_speeds;
  time_speeds.reserve(trucks.size() + 1);
  std::priority_queue<TimeSpeed, VecTimeSpeeds, EarlierEnd> end_speeds;
  float current_speed(0);
  for(auto [s, e, v]: trucks)
  {
//    EndSpeed.emplace();
    while(!end_speeds.empty())
    {
      auto [ne, nv] = end_speeds.top();
      if (ne <= s)
      {
        end_speeds.pop();
        current_speed -= nv;
        time_speeds.emplace_back(ne, current_speed);
      }
      else
      {
        break;
      }
    }

    end_speeds.emplace(e, v);
    current_speed += v;
    time_speeds.emplace_back(s, current_speed);
  }

// Note: There is no begin and end functions for priority_queue, why?
//  for (auto [ne, nv] : end_speeds)
//  {
//    current_speed -= nv;
//    time_speeds.emplace_back(ne, current_speed);
//  }

  while(!end_speeds.empty()) {
    auto [ne, nv] = end_speeds.top();
    end_speeds.pop();
    current_speed -= nv;
    time_speeds.emplace_back(ne, current_speed);
  }

  if (time_speeds.size()==0 || time_speeds.front().first!=0)
  {
    time_speeds.insert(time_speeds.begin(), TimeSpeed(0,0.0));
  }

  return time_speeds;
}

void test_amazonTruckHistgram ()
{
  VecStartEndSpeeds trucks;
  trucks.reserve(4);
  trucks.emplace_back(2, 4, 3.5);
  trucks.emplace_back(5, 9, 4.2);
  trucks.emplace_back(6, 8, 7.3);
  trucks.emplace_back(7, 11, 5.2);

  VecTimeSpeeds time_speeds = std::move(getAmazonTruckHistgram(trucks));

  for (auto [t, s] : time_speeds)
  {
    std::cout << t << "," << s << std::endl;
  }
}

#endif //CPPSANDBOX_LEETCODE_AMAZONTRUCKHISTGRAM_H_
