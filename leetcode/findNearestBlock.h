//
// Created by ZhouP on 4/23/2019.
//

#ifndef CPPSANDBOX_FINDNEARESTBLOCK_H
#define CPPSANDBOX_FINDNEARESTBLOCK_H

#include <string>
#include <unordered_map>

enum Activity:int
{
    School = 0,
    Grocery = 1,
    Cinema = 2
};

typedef std::pair<Activity, int> ActivityUnit;
typedef std::unordered_multimap<Activity, int> ActivityMap;

int findBestSpot (const std::vector<std::vector<Activity>>& SpotActivities,  const std::vector<Activity>& Activities)
{
    size_t R = Activities.size();
    std::vector<std::vector<bool>> DistributionActivities(R);
    size_t N = SpotActivities.size();
    for (std::vector<bool>& bools : DistributionActivities)
    {
        bools.resize(N, false);
    }

//    for (std::vector<Activity>& SpotActivity:SpotActivities)
    for (int k = 0; k < N; ++k) {
        const std::vector<Activity>& sActivity = SpotActivities[k];
        for(const Activity& act : sActivity)
        {
            auto iter = std::find(Activities.begin(), Activities.end(), act);
            if (Activities.end()!=iter)
                DistributionActivities[std::distance(Activities.begin(), iter)][k] = true;
        }
    }

    int left(0);
    int left_index(-1);
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < N; ++j) {
            if (DistributionActivities[i][j])
            {
                left = j;
                left_index = i;
            }
        }
    }

    int right(0);
    for (int j = R-1; j >= 0; --j) {
        for (int k = 0; k < N; ++k) {
            if (DistributionActivities[j][k] && j!=left_index)
            {
                right = k;
            }
        }
    }

    return (left + right)/2;
}


int findBestSpot_Hash (const std::vector<std::vector<Activity>>& SpotActivities,  const std::vector<Activity>& Activities) {

  size_t N = SpotActivities.size();
  typedef std::unordered_multimap<Activity, int> ActivityLocationMap;
  ActivityLocationMap activity_location_map;
  for (int k = 0; k < N; ++k) {
    const std::vector<Activity>& sActivity = SpotActivities[k];
    for(const Activity& act : sActivity)
    {
      activity_location_map.emplace(act, k);
    }
  }

  typedef std::vector<std::vector<int>> ActivitieLocations;
  size_t R = Activities.size();
  ActivitieLocations activitie_locations;
  activitie_locations.resize(R);
//  for(const Activity& act : Activities)
  for (int i = 0; i < R; ++i) {
    const Activity& act = Activities[i];
    auto iters = activity_location_map.equal_range(act);
    for (auto iter = iters.first; iter!=iters.second; ++iter)
    {
      activitie_locations[i].push_back(iter->second);
    }
  }

  int index(-1);
  int min_walking (INT_MAX);
  for (int j = 0; j < N; ++j) {
    int max_activity_walking(-1);
    for (int i = 0; i < R; ++i) {
      max_activity_walking = std::max<int>(max_activity_walking, std::min<int>(*std::lower_bound(activitie_locations[i].begin(), activitie_locations[i].end(), j),
                                                     *std::upper_bound(activitie_locations[i].begin(), activitie_locations[i].end(), j)));
    }
    if (max_activity_walking < min_walking)
    {
      index = j;
      min_walking = max_activity_walking;
    }
  }

  return index;
}

void test_findBestSpot()
{
    std::vector<std::vector<Activity>> SpotActivities = {{Activity::School, Activity ::Cinema}, {}, {Activity ::Grocery}, {Activity ::Cinema}, {Activity ::Grocery}};
    std::vector<Activity> Activities = {Activity::School, Activity ::Grocery};
    std::cout << "The best spot to stay is " << findBestSpot (SpotActivities, Activities);
}

#endif //CPPSANDBOX_FINDNEARESTBLOCK_H
